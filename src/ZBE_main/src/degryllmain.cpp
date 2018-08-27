#include "degryllmain.h"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <set>
#include <vector>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#include "lodepng.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "ZBE/SDL/starters/SDL_Starter.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/core/tools/math/Point.h"

// #include <memory>
// #include <mutex>
// #include <tuple>
//
// #include <GL/glew.h>
// #include <SDL2/SDL_opengl.h>
//
// #include "ZBE/core/system/SysError.h"
//
// #include "ZBE/SDL/starters/SDL_Starter.h"

const int WIDTH = 800;
const int HEIGHT = 600;

const std::string MODEL_PATH = "data/models/chalet.obj";
const std::string TEXTURE_PATH = "data/images/textures/chalet.png";

const int MAX_FRAMES_IN_FLIGHT = 2;

namespace zbe {

const std::vector<const char*> validationLayers = {
  "VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions = {
  VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
  const bool enableValidationLayers = false;
#else
  const bool enableValidationLayers = true;
#endif

VkResult CreateDebugReportCallbackEXT(VkInstance instance,
                                     const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
                                     const VkAllocationCallbacks* pAllocator,
                                     VkDebugReportCallbackEXT* pCallback) {
  auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pCallback);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

void DestroyDebugReportCallbackEXT(VkInstance instance,
                                  VkDebugReportCallbackEXT callback,
                                  const VkAllocationCallbacks* pAllocator) {
  auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
  if (func != nullptr) {
    func(instance, callback, pAllocator);
  }
}

static std::vector<char> readFile(const std::string& filename) {
  std::ifstream file(filename, std::ios::ate | std::ios::binary);

  if (!file.is_open()) {
    printf("ERROR: failed to open file!\n");
  }

  size_t fileSize = (size_t) file.tellg();
  std::vector<char> buffer(fileSize);

  file.seekg(0);
  file.read(buffer.data(), fileSize);
  file.close();

  return buffer;
}

struct QueueFamilyIndices {
  int graphicsFamily = -1;
  int presentFamily = -1;

  bool isComplete() {
    return graphicsFamily >= 0 && presentFamily >= 0;
  }
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

struct Vertex {
  glm::vec3 pos;
  glm::vec3 color;
  glm::vec2 texCoord;

  bool operator==(const Vertex& other) const {
    return pos == other.pos && color == other.color && texCoord == other.texCoord;
  }

  static VkVertexInputBindingDescription getBindingDescription() {
    VkVertexInputBindingDescription bindingDescription = {};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
  }

  static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
    std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[0].offset = offsetof(Vertex, pos);

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[1].offset = offsetof(Vertex, color);

    attributeDescriptions[2].binding = 0;
    attributeDescriptions[2].location = 2;
    attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

    return attributeDescriptions;
  }
};

struct VertexHash {
  std::size_t operator()(zbe::Vertex const& vertex) const noexcept {
    return ((std::hash<glm::vec3>()(vertex.pos) ^
            (std::hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
            (std::hash<glm::vec2>()(vertex.texCoord) << 1);
  }
};

struct UniformBufferObject {
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 proj;
};

/**
* @class SDLVKWindow
* @brief Used to create windows using SDL 2.0. with Vulkan support.
*/
class SDLVKWindow /*: public SDLWindow */{
public:
  SDLVKWindow(const SDLVKWindow&) = delete;  //!< Does not make sense to "copy" a SDLVKWindow.
  void operator=(const SDLVKWindow&) = delete;  //!< Does not make sense to "copy" a SDLVKWindow.

  /** \brief Creates a new SDLVKWindow and a Renderer.
  *
  *  Creates a new SDLVKWindow and a Renderer with the size and flags specified.
  *  \param title Title of the Window.
  *  \param width Width of the Window.
  *  \param height Height of the Window.
  *  \param window_flags Flags for the SDLVKWindow creation. Default no flags.
  *  \param rederer_flags Flags for the Renderer creation. Default no flags.
  */
  SDLVKWindow(const char* title, int width, int height, Uint32 window_flags = 0)
    : sdl(SDL_Starter::getInstance(SDL_INIT_VIDEO)),
      window(SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, window_flags | SDL_WINDOW_VULKAN)),
      instance(nullptr), callback(0), surface(0), physicalDevice(VK_NULL_HANDLE), msaaSamples(VK_SAMPLE_COUNT_1_BIT), device(VK_NULL_HANDLE),
      graphicsQueue(VK_NULL_HANDLE), presentQueue(VK_NULL_HANDLE), swapChain(0), swapChainImages(),
      swapChainImageFormat(VK_FORMAT_UNDEFINED), swapChainExtent{}, swapChainImageViews(),
      swapChainFramebuffers(), renderPass(0), descriptorSetLayout(0), pipelineLayout(0), graphicsPipeline(0),
      commandPool(0), colorImages(), colorImagesMemory(), colorImagesView(),
      depthImages(), depthImagesMemory(), depthImagesView(),
      mipLevels(0), textureImage(0), textureImageMemory(0), textureImageView(0), textureSampler(0),
      vertices(), indices(),
      vertexBuffer(0), vertexBufferMemory(0), indexBuffer(0), indexBufferMemory(0),
      uniformBuffers(), uniformBuffersMemory(), descriptorPool(0), descriptorSets(),
      commandBuffers(), imageAvailableSemaphores(), renderFinishedSemaphores(),
      inFlightFences(), currentFrame(0), framebufferResized(false) {

    //int sdlvk = SDL_Vulkan_LoadLibrary(nullptr);
    //printf("ERRORS IN CONSTRUCTOR? Vulkan load library: %d zbe log: %s SDL:  %s\n", sdlvk, zbe::SysError::getFirstErrorString().c_str(), SDL_GetError());
    initVulkan();
  }

  /** \brief Creates a new SDLVKWindow and a Renderer in a specific position.
  *
  *  Creates a new SDLVKWindow and a Renderer with the position, size and flags specified.
  *  \param title Title of the Window.
  *  \param x X coordinates of the initial position of the window.
  *  \param y Y coordinates of the initial position of the window..
  *  \param width Width of the Window.
  *  \param height Height of the Window.
  *  \param window_flags Flags for the SDLVKWindow creation. Default no flags.
  *  \param rederer_flags Flags for the Renderer creation. Default no flags.
  */
  SDLVKWindow(const char* title, int x, int y, int width, int height, Uint32 window_flags = 0)
    : sdl(SDL_Starter::getInstance(SDL_INIT_VIDEO)),
      window(SDL_CreateWindow(title, x, y, width, height, window_flags | SDL_WINDOW_VULKAN)),
      instance(nullptr), callback(0), surface(0), physicalDevice(VK_NULL_HANDLE), msaaSamples(VK_SAMPLE_COUNT_1_BIT), device(VK_NULL_HANDLE),
      graphicsQueue(VK_NULL_HANDLE), presentQueue(VK_NULL_HANDLE), swapChain(0), swapChainImages(),
      swapChainImageFormat(VK_FORMAT_UNDEFINED), swapChainExtent{}, swapChainImageViews(),
      swapChainFramebuffers(), renderPass(0), descriptorSetLayout(0), pipelineLayout(0), graphicsPipeline(0),
      commandPool(0), colorImages(), colorImagesMemory(), colorImagesView(),
      depthImages(), depthImagesMemory(), depthImagesView(),
      mipLevels(0), textureImage(0), textureImageMemory(0), textureImageView(0), textureSampler(0),
      vertices(), indices(),
      vertexBuffer(0), vertexBufferMemory(0), indexBuffer(0), indexBufferMemory(0),
      uniformBuffers(), uniformBuffersMemory(), descriptorPool(0), descriptorSets(),
      commandBuffers(), imageAvailableSemaphores(), renderFinishedSemaphores(),
      inFlightFences(), currentFrame(0), framebufferResized(false) {
    //int sdlvk = SDL_Vulkan_LoadLibrary(nullptr);
    //printf("ERRORS IN CONSTRUCTOR? Vulkan load library: %d zbe log: %s SDL:  %s\n", sdlvk, zbe::SysError::getFirstErrorString().c_str(), SDL_GetError());
    initVulkan();
  }

  /** \brief Free resources and destroy the Renderer and the SDLVKWindow.
  */
  ~SDLVKWindow() {
    cleanup();
  }

  void drawFrame();

  void waitIdle() {
    vkDeviceWaitIdle(device);
  }

  void setResized() {
    framebufferResized = true;
  }

private:
  static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags,
                                                   VkDebugReportObjectTypeEXT objType,
                                                   uint64_t obj, size_t location, int32_t code,
                                                   const char* layerPrefix, const char* msg, void* userData);

  bool checkValidationLayerSupport();
  std::vector<const char*> getRequiredExtensions();
  void createInstance();
  void setupDebugCallback();
  void createSurface();
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
  bool checkDeviceExtensionSupport(VkPhysicalDevice device);
  bool isDeviceSuitable(VkPhysicalDevice device);
  VkSampleCountFlagBits getMaxUsableSampleCount();
  void pickPhysicalDevice();
  void createLogicalDevice();
  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
  void createSwapChain();
  VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
  void createImageViews();
  VkShaderModule createShaderModule(const std::vector<char>& code);
  void createRenderPass();
  void createDescriptorSetLayout();
  void createGraphicsPipeline();
  void createFramebuffers();
  void createCommandPool();
  void createColorResources();
  VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
  VkFormat findDepthFormat();
  bool hasStencilComponent(VkFormat format);
  void createDepthResources();
  void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
  void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
  void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
  void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
  void createTextureImage();
  void createTextureImageView();
  void createTextureSampler();
  uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
  void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  VkCommandBuffer beginSingleTimeCommands();
  void endSingleTimeCommands(VkCommandBuffer commandBuffer);
  void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
  void loadModel();
  void createVertexBuffer();
  void createIndexBuffer();
  void createUniformBuffer();
  void createDescriptorPool();
  void createDescriptorSets();
  void createCommandBuffers();
  void createSyncObjects();
  void initVulkan();

  void cleanup();

  void cleanupSwapChain();
  void recreateSwapChain();

  void updateUniformBuffer(uint32_t currentImage);

  void printExtensions();

  SDL_Starter &sdl;
  SDL_Window *window;

  VkInstance instance;
  VkDebugReportCallbackEXT callback;
  VkSurfaceKHR surface;

  VkPhysicalDevice physicalDevice;
  VkSampleCountFlagBits msaaSamples;
  VkDevice device;

  VkQueue graphicsQueue;
  VkQueue presentQueue;

  VkSwapchainKHR swapChain;
  std::vector<VkImage> swapChainImages;
  VkFormat swapChainImageFormat;
  VkExtent2D swapChainExtent;
  std::vector<VkImageView> swapChainImageViews;
  std::vector<VkFramebuffer> swapChainFramebuffers;

  VkRenderPass renderPass;
  VkDescriptorSetLayout descriptorSetLayout;
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;

  VkCommandPool commandPool;

  std::vector<VkImage> colorImages;
  std::vector<VkDeviceMemory> colorImagesMemory;
  std::vector<VkImageView> colorImagesView;

  std::vector<VkImage> depthImages;
  std::vector<VkDeviceMemory> depthImagesMemory;
  std::vector<VkImageView> depthImagesView;

  uint32_t mipLevels;
  VkImage textureImage;
  VkDeviceMemory textureImageMemory;
  VkImageView textureImageView;
  VkSampler textureSampler;

  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;
  VkBuffer vertexBuffer;
  VkDeviceMemory vertexBufferMemory;
  VkBuffer indexBuffer;
  VkDeviceMemory indexBufferMemory;

  std::vector<VkBuffer> uniformBuffers;
  std::vector<VkDeviceMemory> uniformBuffersMemory;

  VkDescriptorPool descriptorPool;
  std::vector<VkDescriptorSet> descriptorSets;

  std::vector<VkCommandBuffer> commandBuffers;

  //VkSemaphore imageAvailableSemaphore;
  //VkSemaphore renderFinishedSemaphore;
  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;
  size_t currentFrame;

  bool framebufferResized;
};

void SDLVKWindow::initVulkan() {
  createInstance();
  setupDebugCallback();
  createSurface();
  pickPhysicalDevice();
  createLogicalDevice();
  createSwapChain();
  createImageViews();
  createRenderPass();
  createDescriptorSetLayout();
  createGraphicsPipeline();
  createCommandPool();
  createColorResources();
  createDepthResources();
  createFramebuffers();
  createTextureImage();
  createTextureImageView();
  createTextureSampler();
  loadModel();
  createVertexBuffer();
  createIndexBuffer();
  createUniformBuffer();
  createDescriptorPool();
  createDescriptorSets();
  createCommandBuffers();
  createSyncObjects();
}

void SDLVKWindow::createInstance() {
  if (enableValidationLayers && !checkValidationLayerSupport()) {
    printf("ERROR: validation layers requested, but not available!\n");
    return;
  }

  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "ZBE";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  std::vector<const char*> sdlExtensions = getRequiredExtensions();

  VkInstanceCreateInfo instanceCI = {};
  instanceCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instanceCI.pApplicationInfo = &appInfo;
  instanceCI.enabledExtensionCount = static_cast<uint32_t>(sdlExtensions.size());
  instanceCI.ppEnabledExtensionNames = sdlExtensions.data();

  if (enableValidationLayers) {
    instanceCI.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    instanceCI.ppEnabledLayerNames = validationLayers.data();
  } else {
    instanceCI.enabledLayerCount = 0;
  }

  if (vkCreateInstance(&instanceCI, nullptr, &instance) != VK_SUCCESS) {
    printf("ERROR: failed to create instance!\n");
  }

  printf("SUCCESS!\n");
}

bool SDLVKWindow::checkValidationLayerSupport() {
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for (const char* layerName : validationLayers) {
    bool layerFound = false;

    for (const auto& layerProperties : availableLayers) {
      if (strcmp(layerName, layerProperties.layerName) == 0) {
       layerFound = true;
       break;
      }
    }  // for availableLayers

    if (!layerFound) {
     return false;
    }
  }  // for validationLayers

  return true;
}

void SDLVKWindow::printExtensions() {
  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

  std::vector<VkExtensionProperties> extensions(extensionCount);

  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

  std::cout << "available extensions:" << std::endl;
  for (const auto& extension : extensions) {
    printf("\t%s\n", extension.extensionName);
  }
}

std::vector<const char*> SDLVKWindow::getRequiredExtensions() {
  uint32_t sdlExtensionCount = 0;
  if(!SDL_Vulkan_GetInstanceExtensions(window, &sdlExtensionCount, NULL)) {
    printf("ERROR: failed to retrieving the number of Vulkan extensions needed!:  %s\n", SDL_GetError());
  }

  std::vector<const char*> sdlExtensions(sdlExtensionCount);
  if(!SDL_Vulkan_GetInstanceExtensions(window, &sdlExtensionCount, sdlExtensions.data())) {
    printf("ERROR: failed to retrieving the name of Vulkan extensions needed!:  %s\n", SDL_GetError());
  }

  if (enableValidationLayers) {
    sdlExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
  }

  return sdlExtensions;
}

//VKAPI_ATTR VkBool32 VKAPI_CALL SDLVKWindow::debugCallback(VkDebugReportFlagsEXT flags,
//                                                    VkDebugReportObjectTypeEXT objType,
//                                                    uint64_t obj, size_t location, int32_t code,
//                                                    const char* layerPrefix, const char* msg, void* userData) {
VKAPI_ATTR VkBool32 VKAPI_CALL SDLVKWindow::debugCallback(VkDebugReportFlagsEXT,
                                                   VkDebugReportObjectTypeEXT,
                                                   uint64_t, size_t, int32_t,
                                                   const char*, const char* msg, void*) {
  printf("validation layer: %s\n", msg);
  return VK_FALSE;
}

void SDLVKWindow::setupDebugCallback() {
  if (!enableValidationLayers) return;

  VkDebugReportCallbackCreateInfoEXT callbackCI = {};
  callbackCI.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
  callbackCI.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
  callbackCI.pfnCallback = debugCallback;

  if (CreateDebugReportCallbackEXT(instance, &callbackCI, nullptr, &callback) != VK_SUCCESS) {
    printf("ERROR: failed to set up debug callback!\n");
  }
}

VkSampleCountFlagBits SDLVKWindow::getMaxUsableSampleCount() {
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

    VkSampleCountFlags counts = std::min(physicalDeviceProperties.limits.framebufferColorSampleCounts, physicalDeviceProperties.limits.framebufferDepthSampleCounts);
    if (counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
    if (counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
    if (counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
    if (counts & VK_SAMPLE_COUNT_8_BIT) { return VK_SAMPLE_COUNT_8_BIT; }
    if (counts & VK_SAMPLE_COUNT_4_BIT) { return VK_SAMPLE_COUNT_4_BIT; }
    if (counts & VK_SAMPLE_COUNT_2_BIT) { return VK_SAMPLE_COUNT_2_BIT; }

    return VK_SAMPLE_COUNT_1_BIT;
}

void SDLVKWindow::pickPhysicalDevice() {
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
  if (deviceCount == 0) {
    printf("ERROR: failed to find GPUs with Vulkan support!\n");
  }

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

  for (const auto& device : devices) {
    if (isDeviceSuitable(device)) {
      physicalDevice = device;
      msaaSamples = getMaxUsableSampleCount();
      break;
    }
  }

  if (physicalDevice == VK_NULL_HANDLE) {
    printf("ERROR: failed to find a suitable GPU!\n");
  }
}

bool SDLVKWindow::isDeviceSuitable(VkPhysicalDevice device) {
//  VkPhysicalDeviceProperties deviceProperties;
//  vkGetPhysicalDeviceProperties(device, &deviceProperties);
//
//  VkPhysicalDeviceFeatures deviceFeatures;
//  vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

  QueueFamilyIndices indices = findQueueFamilies(device);

  bool extensionsSupported = checkDeviceExtensionSupport(device);

  bool swapChainAdequate = false;
  if (extensionsSupported) {
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
    swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
  }

  VkPhysicalDeviceFeatures supportedFeatures;
  vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

  return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
}

QueueFamilyIndices SDLVKWindow::findQueueFamilies(VkPhysicalDevice device) {
  QueueFamilyIndices indices;

  uint32_t queueFamilyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

  int i = 0;
  for (const auto& queueFamily : queueFamilies) {
    if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      indices.graphicsFamily = i;
    }

    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
    if (queueFamily.queueCount > 0 && presentSupport) {
      indices.presentFamily = i;
    }

    if (indices.isComplete()) {
      break;
    }
    i++;
  }

  return indices;
}

void SDLVKWindow::createLogicalDevice() {
  QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
  std::set<int> uniqueQueueFamilies = {indices.graphicsFamily, indices.presentFamily};

  float queuePriority = 1.0f;
  for (int queueFamily : uniqueQueueFamilies) {
    VkDeviceQueueCreateInfo queueCI = {};
    queueCI.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCI.queueFamilyIndex = queueFamily;
    queueCI.queueCount = 1;
    queueCI.pQueuePriorities = &queuePriority;
    queueCreateInfos.push_back(queueCI);
  }

  VkPhysicalDeviceFeatures deviceFeatures = {};
  deviceFeatures.samplerAnisotropy = VK_TRUE;
  deviceFeatures.sampleRateShading = VK_TRUE;

  VkDeviceCreateInfo deviceCI = {};
  deviceCI.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  deviceCI.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
  deviceCI.pQueueCreateInfos = queueCreateInfos.data();
  deviceCI.pEnabledFeatures = &deviceFeatures;
  deviceCI.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
  deviceCI.ppEnabledExtensionNames = deviceExtensions.data();

  if (enableValidationLayers) {
    deviceCI.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    deviceCI.ppEnabledLayerNames = validationLayers.data();
  } else {
    deviceCI.enabledLayerCount = 0;
  }

  if (vkCreateDevice(physicalDevice, &deviceCI, nullptr, &device) != VK_SUCCESS) {
    printf("ERROR: failed to create logical device!\n");
  }

  vkGetDeviceQueue(device, indices.graphicsFamily, 0, &graphicsQueue);
  vkGetDeviceQueue(device, indices.presentFamily, 0, &presentQueue);
}

void SDLVKWindow::createSurface() {
  if (!SDL_Vulkan_CreateSurface(window, instance, &surface)) {
    printf("ERROR: failed to create window surface!\n");
  }
}

bool SDLVKWindow::checkDeviceExtensionSupport(VkPhysicalDevice device) {
  uint32_t extensionCount;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

  std::vector<VkExtensionProperties> availableExtensions(extensionCount);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

  std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

  for (const auto& extension : availableExtensions) {
    requiredExtensions.erase(extension.extensionName);
  }

  return requiredExtensions.empty();
}

SwapChainSupportDetails SDLVKWindow::querySwapChainSupport(VkPhysicalDevice device) {
  SwapChainSupportDetails details;

  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

  uint32_t formatCount;
  vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

  if (formatCount != 0) {
    details.formats.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
  }

  uint32_t presentModeCount;
  vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

  if (presentModeCount != 0) {
    details.presentModes.resize(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
  }

  return details;
}

VkSurfaceFormatKHR SDLVKWindow::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
  if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
    return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
  }

  for (const auto& availableFormat : availableFormats) {
    if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
      return availableFormat;
    }
  }

  return availableFormats[0];
}

VkPresentModeKHR SDLVKWindow::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes) {
  VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

  for (const auto& availablePresentMode : availablePresentModes) {
    if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
      return availablePresentMode;
    } else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
      bestMode = availablePresentMode;
    }
  }

  return bestMode;
}

VkExtent2D SDLVKWindow::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
  if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
    return capabilities.currentExtent;
  } else {
    int width, height;
    SDL_Vulkan_GetDrawableSize(window, &width, &height);

    VkExtent2D actualExtent = {
      static_cast<uint32_t>(width),
      static_cast<uint32_t>(height)
    };
    actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

    return actualExtent;
  }
}

void SDLVKWindow::createSwapChain() {
  SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

  VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
  VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
  VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

  uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
  if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
    imageCount = swapChainSupport.capabilities.maxImageCount;
  }

  VkSwapchainCreateInfoKHR swapCI = {};
  swapCI.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  swapCI.surface = surface;
  swapCI.minImageCount = imageCount;
  swapCI.imageFormat = surfaceFormat.format;
  swapCI.imageColorSpace = surfaceFormat.colorSpace;
  swapCI.imageExtent = extent;
  swapCI.imageArrayLayers = 1;
  swapCI.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
  uint32_t queueFamilyIndices[] = {(uint32_t) indices.graphicsFamily, (uint32_t) indices.presentFamily};

  if (indices.graphicsFamily != indices.presentFamily) {
    swapCI.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    swapCI.queueFamilyIndexCount = 2;
    swapCI.pQueueFamilyIndices = queueFamilyIndices;
  } else {
    swapCI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapCI.queueFamilyIndexCount = 0; // Optional
    swapCI.pQueueFamilyIndices = nullptr; // Optional
  }

  swapCI.preTransform = swapChainSupport.capabilities.currentTransform;
  swapCI.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  swapCI.presentMode = presentMode;
  swapCI.clipped = VK_TRUE;
  swapCI.oldSwapchain = VK_NULL_HANDLE;

  if (vkCreateSwapchainKHR(device, &swapCI, nullptr, &swapChain) != VK_SUCCESS) {
    printf("ERROR: failed to create swap chain!\n");
  }

  vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
  swapChainImages.resize(imageCount);
  vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

  swapChainImageFormat = surfaceFormat.format;
  swapChainExtent = extent;
}

void SDLVKWindow::createImageViews() {
  swapChainImageViews.resize(swapChainImages.size());

  for (uint32_t i = 0; i < swapChainImages.size(); i++) {
    swapChainImageViews[i] = createImageView(swapChainImages[i], swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
  }
}

void SDLVKWindow::createGraphicsPipeline() {
  auto vertShaderCode = readFile("data/shaders/working/vert.spv");
  auto fragShaderCode = readFile("data/shaders/working/frag.spv");

  VkShaderModule vertShaderModule;
  VkShaderModule fragShaderModule;

  vertShaderModule = createShaderModule(vertShaderCode);
  fragShaderModule = createShaderModule(fragShaderCode);

  VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
  vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
  vertShaderStageInfo.module = vertShaderModule;
  vertShaderStageInfo.pName = "main";

  VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
  fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  fragShaderStageInfo.module = fragShaderModule;
  fragShaderStageInfo.pName = "main";

  VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

  VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
  vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  auto bindingDescription = Vertex::getBindingDescription();
  auto attributeDescriptions = Vertex::getAttributeDescriptions();

  vertexInputInfo.vertexBindingDescriptionCount = 1;
  vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
  vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
  vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

  VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
  inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  inputAssembly.primitiveRestartEnable = VK_FALSE;

  VkViewport viewport = {};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = (float) swapChainExtent.width;
  viewport.height = (float) swapChainExtent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  VkRect2D scissor = {};
  scissor.offset = {0, 0};
  scissor.extent = swapChainExtent;

  VkPipelineViewportStateCreateInfo viewportState = {};
  viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewportState.viewportCount = 1;
  viewportState.pViewports = &viewport;
  viewportState.scissorCount = 1;
  viewportState.pScissors = &scissor;

  VkPipelineRasterizationStateCreateInfo rasterizer = {};
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  //rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
  rasterizer.depthBiasEnable = VK_FALSE;
  rasterizer.depthBiasConstantFactor = 0.0f; // Optional
  rasterizer.depthBiasClamp = 0.0f; // Optional
  rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

  VkPipelineMultisampleStateCreateInfo multisampling = {};
  multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_TRUE;
  multisampling.rasterizationSamples = msaaSamples;
  multisampling.minSampleShading = .2f; // Optional
  multisampling.pSampleMask = nullptr; // Optional
  multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
  multisampling.alphaToOneEnable = VK_FALSE; // Optional

  VkPipelineDepthStencilStateCreateInfo depthStencil = {};
  depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  depthStencil.depthTestEnable = VK_TRUE;
  depthStencil.depthWriteEnable = VK_TRUE;
  depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
  depthStencil.depthBoundsTestEnable = VK_FALSE;
  depthStencil.minDepthBounds = 0.0f; // Optional
  depthStencil.maxDepthBounds = 1.0f; // Optional
  depthStencil.stencilTestEnable = VK_FALSE;
  depthStencil.front = {}; // Optional
  depthStencil.back = {}; // Optional

  VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
  colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  colorBlendAttachment.blendEnable = VK_FALSE;
  colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
  colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

  VkPipelineColorBlendStateCreateInfo colorBlending = {};
  colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  colorBlending.logicOpEnable = VK_FALSE;
  colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
  colorBlending.attachmentCount = 1;
  colorBlending.pAttachments = &colorBlendAttachment;
  colorBlending.blendConstants[0] = 0.0f; // Optional
  colorBlending.blendConstants[1] = 0.0f; // Optional
  colorBlending.blendConstants[2] = 0.0f; // Optional
  colorBlending.blendConstants[3] = 0.0f; // Optional

  VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 1; // Optional
  pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout; // Optional
  pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
  pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

  if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
    printf("ERROR: failed to create pipeline layout!\n");
  }

  VkGraphicsPipelineCreateInfo pipelineInfo = {};
  pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipelineInfo.stageCount = 2;
  pipelineInfo.pStages = shaderStages;
  pipelineInfo.pVertexInputState = &vertexInputInfo;
  pipelineInfo.pInputAssemblyState = &inputAssembly;
  pipelineInfo.pViewportState = &viewportState;
  pipelineInfo.pRasterizationState = &rasterizer;
  pipelineInfo.pMultisampleState = &multisampling;
  pipelineInfo.pDepthStencilState = &depthStencil;
  pipelineInfo.pColorBlendState = &colorBlending;
  pipelineInfo.pDynamicState = nullptr; // Optional
  pipelineInfo.layout = pipelineLayout;
  pipelineInfo.renderPass = renderPass;
  pipelineInfo.subpass = 0;
  pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
  pipelineInfo.basePipelineIndex = -1; // Optional

  if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
    printf("ERROR: failed to create graphics pipeline!\n");
  }

  vkDestroyShaderModule(device, fragShaderModule, nullptr);
  vkDestroyShaderModule(device, vertShaderModule, nullptr);
}

VkShaderModule SDLVKWindow::createShaderModule(const std::vector<char>& code) {
  VkShaderModuleCreateInfo shaderCI = {};
  shaderCI.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  shaderCI.codeSize = code.size();
  shaderCI.pCode = reinterpret_cast<const uint32_t*>(code.data());

  VkShaderModule shaderModule;
  if (vkCreateShaderModule(device, &shaderCI, nullptr, &shaderModule) != VK_SUCCESS) {
    printf("ERROR: failed to create shader module!\n");
  }

  return shaderModule;
}

void SDLVKWindow::createRenderPass() {
  VkAttachmentDescription colorAttachment = {};
  colorAttachment.format = swapChainImageFormat;
  colorAttachment.samples = msaaSamples;
  colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  colorAttachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkAttachmentDescription depthAttachment = {};
  depthAttachment.format = findDepthFormat();
  depthAttachment.samples = msaaSamples;
  depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkAttachmentDescription colorAttachmentResolve = {};
  colorAttachmentResolve.format = swapChainImageFormat;
  colorAttachmentResolve.samples = VK_SAMPLE_COUNT_1_BIT;
  colorAttachmentResolve.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  colorAttachmentResolve.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  colorAttachmentResolve.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  colorAttachmentResolve.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  colorAttachmentResolve.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  colorAttachmentResolve.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  VkAttachmentReference colorAttachmentRef = {};
  colorAttachmentRef.attachment = 0;
  colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkAttachmentReference depthAttachmentRef = {};
  depthAttachmentRef.attachment = 1;
  depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkAttachmentReference colorAttachmentResolveRef = {};
  colorAttachmentResolveRef.attachment = 2;
  colorAttachmentResolveRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  VkSubpassDescription subpass = {};
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &colorAttachmentRef;
  subpass.pDepthStencilAttachment = &depthAttachmentRef;
  subpass.pResolveAttachments = &colorAttachmentResolveRef;

  VkSubpassDependency dependency = {};
  dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
  dependency.dstSubpass = 0;
  dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.srcAccessMask = 0;
  dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

  std::array<VkAttachmentDescription, 3> attachments = {colorAttachment, depthAttachment, colorAttachmentResolve};
  VkRenderPassCreateInfo renderPassInfo = {};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
  renderPassInfo.pAttachments = attachments.data();
  renderPassInfo.subpassCount = 1;
  renderPassInfo.pSubpasses = &subpass;
  renderPassInfo.dependencyCount = 1;
  renderPassInfo.pDependencies = &dependency;

  if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
    printf("ERROR: failed to create render pass!\n");
  }
}

void SDLVKWindow::createFramebuffers() {
  swapChainFramebuffers.resize(swapChainImageViews.size());

  for (size_t i = 0; i < swapChainImageViews.size(); i++) {
    std::array<VkImageView, 3> attachments = {
      colorImagesView[i],
      depthImagesView[i],
      swapChainImageViews[i]
    };

    VkFramebufferCreateInfo framebufferInfo = {};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    framebufferInfo.pAttachments = attachments.data();
    framebufferInfo.width = swapChainExtent.width;
    framebufferInfo.height = swapChainExtent.height;
    framebufferInfo.layers = 1;

    if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
      printf("ERROR: failed to create framebuffer!\n");
    }
  }  // for swapChainImageViews
}

void SDLVKWindow::createCommandPool() {
  QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

  VkCommandPoolCreateInfo poolInfo = {};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;
  poolInfo.flags = 0; // Optional

  if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
    printf("ERROR: failed to create command pool!\n");
  }
}

void SDLVKWindow::createCommandBuffers() {
  commandBuffers.resize(swapChainFramebuffers.size());

  VkCommandBufferAllocateInfo allocInfo = {};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = commandPool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

  if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
    printf("ERROR: failed to allocate command buffers!\n");
  }

  for (size_t i = 0; i < commandBuffers.size(); i++) {
    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
    beginInfo.pInheritanceInfo = nullptr; // Optional

    if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
      printf("ERROR: failed to begin recording command buffer!\n");
    }

    VkRenderPassBeginInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = renderPass;
    renderPassInfo.framebuffer = swapChainFramebuffers[i];
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = swapChainExtent;

    std::array<VkClearValue, 2> clearValues = {};
    clearValues[0].color = {0.0f, 0.0f, 0.0f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};

    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

    VkBuffer vertexBuffers[] = {vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);

    vkCmdBindIndexBuffer(commandBuffers[i], indexBuffer, 0, VK_INDEX_TYPE_UINT32);

    vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[i], 0, nullptr);
    //vkCmdDraw(commandBuffers[i], static_cast<uint32_t>(vertices.size()), 1, 0, 0);
    vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
    vkCmdEndRenderPass(commandBuffers[i]);

    if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
      printf("ERROR: failed to record command buffer!\n");
    }
  }  // for commandBuffers
}

void SDLVKWindow::createSyncObjects() {
  imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
  renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
  inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

  VkSemaphoreCreateInfo semaphoreInfo = {};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  VkFenceCreateInfo fenceInfo = {};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS
    || vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS
    || vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
      printf("ERROR: failed to create semaphores for a frame!\n");
    }
  }  // for MAX_FRAMES_IN_FLIGHT
}

void SDLVKWindow::drawFrame() {
  vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());

  uint32_t imageIndex;
  VkResult result = vkAcquireNextImageKHR(device, swapChain, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

  if (result == VK_ERROR_OUT_OF_DATE_KHR) {
    recreateSwapChain();
    return;
  } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
    printf("ERROR: failed to acquire swap chain image!\n");
  }

  updateUniformBuffer(imageIndex);

  VkSubmitInfo submitInfo = {};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

  VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
  VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

  VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;

  vkResetFences(device, 1, &inFlightFences[currentFrame]);

  if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
    printf("ERROR: failed to submit draw command buffer!\n");
  }

  VkPresentInfoKHR presentInfo = {};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = signalSemaphores;
  VkSwapchainKHR swapChains[] = {swapChain};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;
  presentInfo.pImageIndices = &imageIndex;
  presentInfo.pResults = nullptr; // Optional

  vkQueuePresentKHR(presentQueue, &presentInfo);

  if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
    framebufferResized = false;
    recreateSwapChain();
  } else if (result != VK_SUCCESS) {
    printf("ERROR: failed to present swap chain image!\n");
  }

  currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void SDLVKWindow::cleanup() {
  cleanupSwapChain();

  vkDestroySampler(device, textureSampler, nullptr);
  vkDestroyImageView(device, textureImageView, nullptr);
  vkDestroyImage(device, textureImage, nullptr);
  vkFreeMemory(device, textureImageMemory, nullptr);

  vkDestroyDescriptorPool(device, descriptorPool, nullptr);

  vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);

  for (size_t i = 0; i < swapChainImages.size(); i++) {
    vkDestroyBuffer(device, uniformBuffers[i], nullptr);
    vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
  }

  vkDestroyBuffer(device, indexBuffer, nullptr);
  vkFreeMemory(device, indexBufferMemory, nullptr);

  vkDestroyBuffer(device, vertexBuffer, nullptr);
  vkFreeMemory(device, vertexBufferMemory, nullptr);

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
    vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
    vkDestroyFence(device, inFlightFences[i], nullptr);
  }

  vkDestroyCommandPool(device, commandPool, nullptr);

  vkDestroyDevice(device, nullptr);

  if (enableValidationLayers) {
    DestroyDebugReportCallbackEXT(instance, callback, nullptr);
  }

  vkDestroySurfaceKHR(instance, surface, nullptr);
  vkDestroyInstance(instance, nullptr);

//  glfwDestroyWindow(window);
//
//  glfwTerminate();
}

void SDLVKWindow::cleanupSwapChain() {
  for (size_t i = 0; i < swapChainImages.size(); i++) {
    vkDestroyImageView(device, colorImagesView[i], nullptr);
    vkDestroyImage(device, colorImages[i], nullptr);
    vkFreeMemory(device, colorImagesMemory[i], nullptr);
    vkDestroyImageView(device, depthImagesView[i], nullptr);
    vkDestroyImage(device, depthImages[i], nullptr);
    vkFreeMemory(device, depthImagesMemory[i], nullptr);
  }

  for (auto framebuffer : swapChainFramebuffers) {
    vkDestroyFramebuffer(device, framebuffer, nullptr);
  }

  vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

  vkDestroyPipeline(device, graphicsPipeline, nullptr);
  vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
  vkDestroyRenderPass(device, renderPass, nullptr);

  for (auto imageView : swapChainImageViews) {
    vkDestroyImageView(device, imageView, nullptr);
  }

  vkDestroySwapchainKHR(device, swapChain, nullptr);
}

void SDLVKWindow::recreateSwapChain() {
  int width = 0, height = 0;
  while (width == 0 || height == 0) {
    SDL_Vulkan_GetDrawableSize(window, &width, &height);
    SDL_WaitEvent(nullptr);
  }

  vkDeviceWaitIdle(device);

  cleanupSwapChain();

  createSwapChain();
  createImageViews();
  createRenderPass();
  createGraphicsPipeline();
  createDepthResources();
  createFramebuffers();
  createCommandBuffers();
}

void SDLVKWindow::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
  VkBufferCreateInfo bufferInfo = {};
  bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bufferInfo.size = size;
  bufferInfo.usage = usage;
  bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
      printf("ERROR: failed to create buffer!\n");
  }

  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

  VkMemoryAllocateInfo allocInfo = {};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

  if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
      printf("ERROR: failed to allocate memory!\n");
  }

  if (vkBindBufferMemory(device, buffer, bufferMemory, 0) != VK_SUCCESS) {
      printf("ERROR: failed to bind buffer memory!\n");
  }
}

void SDLVKWindow::createVertexBuffer() {
  VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

  void* data;
  vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
      memcpy(data, vertices.data(), (size_t) bufferSize);
  vkUnmapMemory(device, stagingBufferMemory);

  createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

  copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

  vkDestroyBuffer(device, stagingBuffer, nullptr);
  vkFreeMemory(device, stagingBufferMemory, nullptr);
}

uint32_t SDLVKWindow::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

  for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
    if ((typeFilter & (1 << i))
    && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
      return i;
    }
  }

  printf("ERROR: failed to find suitable memory type!\n");
  return 0;
}

void SDLVKWindow::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
  VkCommandBuffer commandBuffer = beginSingleTimeCommands();

  VkBufferCopy copyRegion = {};
  copyRegion.size = size;
  vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

  endSingleTimeCommands(commandBuffer);
}

void SDLVKWindow::createIndexBuffer() {
  VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

  void* data;
  vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
  memcpy(data, indices.data(), (size_t) bufferSize);
  vkUnmapMemory(device, stagingBufferMemory);

  createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

  copyBuffer(stagingBuffer, indexBuffer, bufferSize);

  vkDestroyBuffer(device, stagingBuffer, nullptr);
  vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void SDLVKWindow::createDescriptorSetLayout() {
  VkDescriptorSetLayoutBinding uboLayoutBinding = {};
  uboLayoutBinding.binding = 0;
  uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  uboLayoutBinding.descriptorCount = 1;
  uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  uboLayoutBinding.pImmutableSamplers = nullptr; // Optional

  VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
  samplerLayoutBinding.binding = 1;
  samplerLayoutBinding.descriptorCount = 1;
  samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  samplerLayoutBinding.pImmutableSamplers = nullptr;
  samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

  std::array<VkDescriptorSetLayoutBinding, 2> bindings = {uboLayoutBinding, samplerLayoutBinding};
  VkDescriptorSetLayoutCreateInfo layoutInfo = {};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
  layoutInfo.pBindings = bindings.data();

  if (vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
    printf("ERROR: failed to create descriptor set layout!\n");
  }
}

void SDLVKWindow::createUniformBuffer() {
  VkDeviceSize bufferSize = sizeof(UniformBufferObject);

  uniformBuffers.resize(swapChainImages.size());
  uniformBuffersMemory.resize(swapChainImages.size());

  for (size_t i = 0; i < swapChainImages.size(); i++) {
    createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
  }
}

void SDLVKWindow::updateUniformBuffer(uint32_t currentImage) {
  static auto startTime = std::chrono::high_resolution_clock::now();

  auto currentTime = std::chrono::high_resolution_clock::now();
  float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

  UniformBufferObject ubo = {};
  ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float) swapChainExtent.height, 0.1f, 10.0f);
  ubo.proj[1][1] *= -1;

  void* data;
  vkMapMemory(device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
    memcpy(data, &ubo, sizeof(ubo));
  vkUnmapMemory(device, uniformBuffersMemory[currentImage]);
}

void SDLVKWindow::createDescriptorPool() {
  std::array<VkDescriptorPoolSize, 2> poolSizes = {};
  poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  poolSizes[0].descriptorCount = static_cast<uint32_t>(swapChainImages.size());
  poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  poolSizes[1].descriptorCount = static_cast<uint32_t>(swapChainImages.size());

  VkDescriptorPoolCreateInfo poolInfo = {};
  poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
  poolInfo.pPoolSizes = poolSizes.data();
  poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size());

  if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
    printf("ERROR: failed to create descriptor pool!\n");
  }
}

void SDLVKWindow::createDescriptorSets() {
  std::vector<VkDescriptorSetLayout> layouts(swapChainImages.size(), descriptorSetLayout);
  VkDescriptorSetAllocateInfo allocInfo = {};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptorPool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImages.size());
  allocInfo.pSetLayouts = layouts.data();

  descriptorSets.resize(swapChainImages.size());

  if (vkAllocateDescriptorSets(device, &allocInfo, &descriptorSets[0]) != VK_SUCCESS) {
    printf("ERROR: failed to allocate descriptor sets!\n");
  }

  for (size_t i = 0; i < swapChainImages.size(); i++) {

    VkDescriptorBufferInfo bufferInfo = {};
    bufferInfo.buffer = uniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(UniformBufferObject);

    VkDescriptorImageInfo imageInfo = {};
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = textureImageView;
    imageInfo.sampler = textureSampler;

    std::array<VkWriteDescriptorSet, 2> descriptorWrites = {};

    descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrites[0].dstSet = descriptorSets[i];
    descriptorWrites[0].dstBinding = 0;
    descriptorWrites[0].dstArrayElement = 0;
    descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrites[0].descriptorCount = 1;
    descriptorWrites[0].pBufferInfo = &bufferInfo;

    descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrites[1].dstSet = descriptorSets[i];
    descriptorWrites[1].dstBinding = 1;
    descriptorWrites[1].dstArrayElement = 0;
    descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWrites[1].descriptorCount = 1;
    descriptorWrites[1].pImageInfo = &imageInfo;

    vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
  }
}

void SDLVKWindow::generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels) {
  VkFormatProperties formatProperties;
  vkGetPhysicalDeviceFormatProperties(physicalDevice, imageFormat, &formatProperties);

  if (!(formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)) {
    printf("ERROR: texture image format does not support linear blitting!\n");
    return;
  }

  VkCommandBuffer commandBuffer = beginSingleTimeCommands();

  VkImageMemoryBarrier barrier = {};
  barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  barrier.image = image;
  barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  barrier.subresourceRange.baseArrayLayer = 0;
  barrier.subresourceRange.layerCount = 1;
  barrier.subresourceRange.levelCount = 1;

  int32_t mipWidth = texWidth;
  int32_t mipHeight = texHeight;

  for (uint32_t i = 1; i < mipLevels; i++) {
    barrier.subresourceRange.baseMipLevel = i - 1;
    barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

    vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);

    VkImageBlit blit = {};
    blit.srcOffsets[0] = { 0, 0, 0 };
    blit.srcOffsets[1] = { mipWidth, mipHeight, 1 };
    blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    blit.srcSubresource.mipLevel = i - 1;
    blit.srcSubresource.baseArrayLayer = 0;
    blit.srcSubresource.layerCount = 1;
    blit.dstOffsets[0] = { 0, 0, 0 };
    blit.dstOffsets[1] = { mipWidth > 1 ? mipWidth / 2 : 1, mipHeight > 1 ? mipHeight / 2 : 1, 1 };
    blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    blit.dstSubresource.mipLevel = i;
    blit.dstSubresource.baseArrayLayer = 0;
    blit.dstSubresource.layerCount = 1;

    vkCmdBlitImage(commandBuffer, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &blit, VK_FILTER_LINEAR);

    barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);

    if (mipWidth > 1) mipWidth /= 2;
    if (mipHeight > 1) mipHeight /= 2;
  }

  barrier.subresourceRange.baseMipLevel = mipLevels - 1;
  barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
  barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
  barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

  vkCmdPipelineBarrier(commandBuffer,
      VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
      0, nullptr,
      0, nullptr,
      1, &barrier);

  endSingleTimeCommands(commandBuffer);
}

void SDLVKWindow::createTextureImage() {
  unsigned w, h;
  std::vector<unsigned char> image;
  unsigned error = lodepng::decode(image, w, h, TEXTURE_PATH.c_str());
  if(error != 0)  {
    zbe::SysError::setError(std::string("ERROR: lodepng could not load the texture: ") + lodepng_error_text(error));
  }

  mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(w, h)))) + 1;

  VkDeviceSize imageSize = w * h * 4;
  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;

  createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

  void* data;
  vkMapMemory(device, stagingBufferMemory, 0, imageSize, 0, &data);
    memcpy(data, image.data(), static_cast<size_t>(imageSize));
  vkUnmapMemory(device, stagingBufferMemory);

  createImage(w, h, mipLevels, VK_SAMPLE_COUNT_1_BIT, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, textureImage, textureImageMemory);

  transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, mipLevels);
  copyBufferToImage(stagingBuffer, textureImage, static_cast<uint32_t>(w), static_cast<uint32_t>(h));
  //transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, mipLevels);

  generateMipmaps(textureImage, VK_FORMAT_R8G8B8A8_UNORM, w, h, mipLevels);

  vkDestroyBuffer(device, stagingBuffer, nullptr);
  vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void SDLVKWindow::createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory) {
  VkImageCreateInfo imageInfo = {};
  imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  imageInfo.imageType = VK_IMAGE_TYPE_2D;
  imageInfo.extent.width = width;
  imageInfo.extent.height = height;
  imageInfo.extent.depth = 1;
  imageInfo.mipLevels = mipLevels;
  imageInfo.arrayLayers = 1;
  imageInfo.format = format;
  imageInfo.tiling = tiling;
  imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  imageInfo.usage = usage;
  imageInfo.samples = numSamples;
  imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if (vkCreateImage(device, &imageInfo, nullptr, &image) != VK_SUCCESS) {
    printf("ERROR: failed to create image!\n");
  }

  VkMemoryRequirements memRequirements;
  vkGetImageMemoryRequirements(device, image, &memRequirements);

  VkMemoryAllocateInfo allocInfo = {};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

  if (vkAllocateMemory(device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
    printf("ERROR: failed to allocate image memory!\n");
  }

  vkBindImageMemory(device, image, imageMemory, 0);
}

VkCommandBuffer SDLVKWindow::beginSingleTimeCommands() {
    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = commandPool;
    allocInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    return commandBuffer;
}

void SDLVKWindow::endSingleTimeCommands(VkCommandBuffer commandBuffer) {
    vkEndCommandBuffer(commandBuffer);

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(graphicsQueue);

    vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}

void SDLVKWindow::transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels) {
  VkCommandBuffer commandBuffer = beginSingleTimeCommands();

  VkImageMemoryBarrier barrier = {};
  barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  barrier.oldLayout = oldLayout;
  barrier.newLayout = newLayout;
  barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.image = image;

  if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    if (hasStencilComponent(format)) {
      barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
    }
  } else {
    barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  }


  barrier.subresourceRange.baseMipLevel = 0;
  barrier.subresourceRange.levelCount = mipLevels;
  barrier.subresourceRange.baseArrayLayer = 0;
  barrier.subresourceRange.layerCount = 1;

  VkPipelineStageFlags sourceStage;
  VkPipelineStageFlags destinationStage;

  if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
    barrier.srcAccessMask = 0;
    barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

    sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
  } else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
  } else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
    barrier.srcAccessMask = 0;
    barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
  } else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL) {
    barrier.srcAccessMask = 0;
    barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    destinationStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  } else {
    printf("ERROR: unsupported layout transition!\n");
    return;
  }

  vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);

  endSingleTimeCommands(commandBuffer);
}

void SDLVKWindow::copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) {
  VkCommandBuffer commandBuffer = beginSingleTimeCommands();

  VkBufferImageCopy region = {};
  region.bufferOffset = 0;
  region.bufferRowLength = 0;
  region.bufferImageHeight = 0;

  region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  region.imageSubresource.mipLevel = 0;
  region.imageSubresource.baseArrayLayer = 0;
  region.imageSubresource.layerCount = 1;

  region.imageOffset = {0, 0, 0};
  region.imageExtent = {
    width,
    height,
    1
  };

  vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

  endSingleTimeCommands(commandBuffer);
}

void SDLVKWindow::createTextureImageView() {
  textureImageView = createImageView(textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT, mipLevels);
}

VkImageView SDLVKWindow::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels) {
  VkImageViewCreateInfo viewInfo = {};
  viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  viewInfo.image = image;
  viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
  viewInfo.format = format;
  viewInfo.subresourceRange.aspectMask = aspectFlags;
  viewInfo.subresourceRange.baseMipLevel = 0;
  viewInfo.subresourceRange.levelCount = mipLevels;
  viewInfo.subresourceRange.baseArrayLayer = 0;
  viewInfo.subresourceRange.layerCount = 1;

  VkImageView imageView;
  if (vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
    printf("ERROR: failed to create texture image view!\n");
  }

  return imageView;
}

void SDLVKWindow::createTextureSampler() {
  VkSamplerCreateInfo samplerInfo = {};
  samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  samplerInfo.magFilter = VK_FILTER_LINEAR;
  samplerInfo.minFilter = VK_FILTER_LINEAR;
  samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.anisotropyEnable = VK_TRUE;
  samplerInfo.maxAnisotropy = 16;
  samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
  samplerInfo.unnormalizedCoordinates = VK_FALSE;
  samplerInfo.compareEnable = VK_FALSE;
  samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
  samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
  samplerInfo.mipLodBias = 0.0f;
  samplerInfo.minLod = 0.0f;
  samplerInfo.maxLod = static_cast<float>(mipLevels);

  if (vkCreateSampler(device, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS) {
    printf("ERROR: failed to create texture sampler!\n");
  }
}

void SDLVKWindow::createColorResources() {
  VkFormat colorFormat = swapChainImageFormat;

  colorImages.resize(swapChainImages.size());
  colorImagesMemory.resize(swapChainImages.size());
  colorImagesView.resize(swapChainImages.size());

  for (size_t i = 0; i < swapChainImageViews.size(); i++) {
    createImage(swapChainExtent.width, swapChainExtent.height, 1, msaaSamples, colorFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, colorImages[i], colorImagesMemory[i]);
    colorImagesView[i] = createImageView(colorImages[i], colorFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);

    transitionImageLayout(colorImages[i], colorFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, 1);
  }
}

VkFormat SDLVKWindow::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
  for (VkFormat format : candidates) {
    VkFormatProperties props;
    vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

    if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
      return format;
    } else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
      return format;
    }
  }

  printf("ERROR: failed to find supported format!\n");
}

VkFormat SDLVKWindow::findDepthFormat() {
  return findSupportedFormat(
    {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
    VK_IMAGE_TILING_OPTIMAL,
    VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
  );
}

bool SDLVKWindow::hasStencilComponent(VkFormat format) {
    return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
}

void SDLVKWindow::createDepthResources() {
  VkFormat depthFormat = findDepthFormat();

  depthImages.resize(swapChainImages.size());
  depthImagesMemory.resize(swapChainImages.size());
  depthImagesView.resize(swapChainImages.size());

  for (size_t i = 0; i < swapChainImageViews.size(); i++) {
    createImage(swapChainExtent.width, swapChainExtent.height, 1, msaaSamples, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImages[i], depthImagesMemory[i]);
    depthImagesView[i] = createImageView(depthImages[i], depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, 1);
    transitionImageLayout(depthImages[i], depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, 1);
  }
}

void SDLVKWindow::loadModel() {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string err;

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, MODEL_PATH.c_str())) {
    printf("%s", err.c_str());
  }

  std::unordered_map<Vertex, uint32_t, VertexHash> uniqueVertices = {};

  for (const auto& shape : shapes) {
    for (const auto& index : shape.mesh.indices) {
      Vertex vertex = {};

      vertex.pos = {
        attrib.vertices[3 * index.vertex_index + 0],
        attrib.vertices[3 * index.vertex_index + 1],
        attrib.vertices[3 * index.vertex_index + 2]
      };

      vertex.texCoord = {
        attrib.texcoords[2 * index.texcoord_index + 0],
        1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
      };

      vertex.color = {1.0f, 1.0f, 1.0f};

      if (uniqueVertices.count(vertex) == 0) {
        uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
        vertices.push_back(vertex);
      }

      indices.push_back(uniqueVertices[vertex]);
    }
  }
}

}  // namespace zbe

void vulkantest() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Event event;

  zbe::SDLVKWindow windows("Prueba Vulkan", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);

  bool keep = true;
  while(keep) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_WINDOWEVENT) {
        switch (event.window.event) {
        case SDL_WINDOWEVENT_CLOSE:
          keep = false;
          break;
        case SDL_WINDOWEVENT_RESIZED:
          windows.setResized();
        break;
        }
      }  // if SDL_WINDOWEVENT
    }
   windows.drawFrame();
  }

  windows.waitIdle();
}

struct TileComparator {
  bool operator() (const zbe::Point<4>& lhs, const zbe::Point<4>& rhs) const {
    if (lhs[2] < rhs[2]) {return true;}
    else if (lhs[2] > rhs[2]) {return false;}

    if (lhs[3] < rhs[3]) {return true;}
    else if (lhs[3] > rhs[3]) {return false;}

    if (lhs[1] < rhs[1]) {return true;}
    else if (lhs[1] > rhs[1]) {return false;}

    if (lhs[0] < rhs[0]) {return true;}
    else if (lhs[0] > rhs[0]) {return false;}

    return false;
  }
};

typedef std::set<zbe::Point<4>, TileComparator> Tile;

void drawfloor(std::shared_ptr<zbe::SDLWindow> window, uint64_t* floortile, int x, int y, int c, int isooffset, int offsetx = 50, int offsety = 50) {
  SDL_Rect src, dst;
  const int iw = 16;
  const int ih = 9;
  const int ihw = iw / 2;
  const int ihh = ih / 2;
  src.x = 0;
  src.y = 0;
  src.w = 16;
  src.h = 9;

  int offset = (isooffset) ? ihw : 0;

  dst.x = offsetx + x * iw + offset;
  dst.y = offsety + y * ihh - ih * c;
  dst.w = 16;
  dst.h = 9;
  //printf("x: %d, y: %d\n", dst.x, dst.y); fflush(stdout);
  SDL_Texture* tex = window->getImgStore()->getTexture(floortile[abs(c) % 2]);
  window->render(tex , &src, &dst);
}

void drawleftwall(std::shared_ptr<zbe::SDLWindow> window, uint64_t tile, int x, int y, int c, int isooffset, int offsetx = 50, int offsety = 50) {
  SDL_Rect src, dst;
  const int iw = 16;
  const int ih = 9;
  const int ihw = iw / 2;
  const int ihh = ih / 2;
  src.x = 0;
  src.y = 0;
  src.w = 8;
  src.h = 14;

  int offset = (isooffset) ? ihw : 0;

  dst.x = offsetx + x * iw + offset;
  dst.y = offsety + y * ihh - ih * c + ihh;
  dst.w = 8;
  dst.h = 14;
  //printf("x: %d, y: %d\n", dst.x, dst.y); fflush(stdout);
  SDL_Texture* tex = window->getImgStore()->getTexture(tile);
  window->render(tex , &src, &dst);
}

void drawrightwall(std::shared_ptr<zbe::SDLWindow> window, uint64_t tile, int x, int y, int c, int isooffset, int offsetx = 50, int offsety = 50) {
  SDL_Rect src, dst;
  const int iw = 16;
  const int ih = 9;
  const int ihw = iw / 2;
  const int ihh = ih / 2;
  src.x = 0;
  src.y = 0;
  src.w = 8;
  src.h = 14;

  int offset = (isooffset) ? ihw : 0;

  dst.x = offsetx + x * iw + offset + ihw;
  dst.y = offsety + y * ihh - ih * c + ihh;
  dst.w = 8;
  dst.h = 14;
  //printf("x: %d, y: %d\n", dst.x, dst.y); fflush(stdout);
  SDL_Texture* tex = window->getImgStore()->getTexture(tile);
  window->render(tex , &src, &dst);
}

void drawprota(std::shared_ptr<zbe::SDLWindow> window, uint64_t tile, int x, int y, int c, int isooffset, int offsetx = 50, int offsety = 50) {
  SDL_Rect src, dst;
  const int iw = 16;
  const int ih = 9;
  const int ihw = iw / 2;
  const int ihh = ih / 2;
  src.x = 0;
  src.y = 0;
  src.w = 11;
  src.h = 38;

  int offset = (isooffset) ? ihw : 0;

  dst.x = offsetx + x * iw + offset + 4;
  dst.y = offsety + y * ihh - ih * c - 32;
  dst.w = 11;
  dst.h = 38;
  //printf("x: %d, y: %d\n", dst.x, dst.y); fflush(stdout);
  SDL_Texture* tex = window->getImgStore()->getTexture(tile);
  window->render(tex , &src, &dst);
}

void draw(std::shared_ptr<zbe::SDLWindow> window, uint64_t* floortile, uint64_t izqtile, uint64_t dertile, std::vector<std::vector<std::vector<int>>> m, uint64_t protatile, std::vector<int> prota, int offsetx = 50, int offsety = 50) {
  int layers = m.size();
  int rows = m[0].size();
  int cols = m[0][0].size();

  for (int row = 0; row < rows; row++) {
    for (int layer = 0; layer < layers; layer++) {
      for (int col = 0; col < cols; col++) {
        if (m[layer][row][col] == 0) continue;
        drawleftwall(window, izqtile, col, row, layer, row % 2, offsetx, offsety);
        drawrightwall(window, dertile, col, row, layer, row % 2, offsetx, offsety);
        drawfloor(window, floortile, col, row, layer, row % 2, offsetx, offsety);
        if (prota[2] == layer && prota[1] == row && prota[0] == col) drawprota(window, protatile, prota[0], prota[1], prota[2], row % 2, offsetx, offsety);
      }
    }
  }
}

void draw2(std::shared_ptr<zbe::SDLWindow> window, uint64_t* floortile, uint64_t izqtile, uint64_t dertile, std::vector<std::vector<std::vector<int>>> m, uint64_t protatile, std::vector<int> prota, int offsetx = 50, int offsety = 100) {
  offsetx += 200;
  int layers = m.size();
  int rows = m[0].size();
  int cols = m[0][0].size();

  for (int row = 0; row < rows; row++) {
    for (int layer = 0; layer < layers; layer++) {
      for (int col = 0; col < cols; col++) {
        if (m[layer][row][col] == 0) continue;
        drawleftwall(window, izqtile, col-prota[0], row-prota[1], layer-prota[2], row % 2, offsetx, offsety);
        drawrightwall(window, dertile, col-prota[0], row-prota[1], layer-prota[2], row % 2, offsetx, offsety);
        drawfloor(window, floortile, col-prota[0], row-prota[1], layer-prota[2], row % 2, offsetx, offsety);
        if (prota[2] == layer && prota[1] == row && prota[0] == col) drawprota(window, protatile, 0, 0, 0, row % 2, offsetx, offsety);
      }
    }
  }
}

void draw3(std::shared_ptr<zbe::SDLWindow> window, uint64_t* floortile, uint64_t izqtile, uint64_t dertile, Tile m, uint64_t protatile, std::vector<int> prota, int offsetx = 50, int offsety = 50) {
  offsetx += 200;

  for(zbe::Point<4> t : m) {
    if (t[0] == 0) {
      drawleftwall(window, izqtile, t[1]-prota[0], t[2]-prota[1], t[3]-prota[2], int(t[2]) % 2, offsetx, offsety);
      drawrightwall(window, dertile, t[1]-prota[0], t[2]-prota[1], t[3]-prota[2], int(t[2]) % 2, offsetx, offsety);
    } else if (t[0] == 1) {
      drawfloor(window, floortile, t[1]-prota[0], t[2]-prota[1], t[3]-prota[2], int(t[2]) % 2, offsetx, offsety);
    } else {
      drawprota(window, protatile, 0, 0, 0, int(prota[1]) % 2, offsetx, offsety);
    }
  }
  //drawprota(window, protatile, 0, 0, 0, int(prota[1]) % 2, offsetx, offsety);
}

void fixposition(std::vector<int>& prota, std::vector<std::vector<std::vector<int> > > m) {
  while (prota[2] < m.size()-1 && m[prota[2]][prota[1]][prota[0]] != 0) {
    prota[2]++;
  }

  while (prota[2] > 0 && m[prota[2]][prota[1]][prota[0]] != 1) {
    prota[2]--;
  }
}

void walkLeft(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z);
void walkUpLeft(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z);
void walkUp(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z);
void walkUpRight(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z);
void walkRight(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z);
void walkDownRight(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z);
void walkDonw(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z);
void walkDownLeft(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z);

void update(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int &ceiling, int &floor, int x, int y, int z) {
  int d = m.size();
  floor = z;
  while ((floor > 0) && (m[floor][y][x] == 0)) floor--;
  while ((floor+1 < ceiling) && (m[floor+1][y][x] == 1)) {
    floor++;
    m2.insert(zbe::Point<4>{0, x, y, floor});
  }
  m2.insert(zbe::Point<4>{1, x, y, floor});

  while ((ceiling < d) && (m[ceiling][y][x]) == 0) ceiling++;
}

void walkLeft(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z) {
  int d = m.size();
  int h = m[0].size();
  int w = m[0][0].size();
  if (x < 0 || y < 0 || z < 0
  ||  x >= w || y >= h || z >= d) return;

  int floor = z;
  update(m, m2, ceiling, floor, x, y, z);

  walkUpLeft(m, m2, ceiling, x-1, y-1, floor);
  walkLeft(m, m2, ceiling, x-1, y, floor);
  walkDownLeft(m, m2, ceiling, x-1, y+1, floor);
}

void walkUpLeft(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z) {
  int d = m.size();
  int h = m[0].size();
  int w = m[0][0].size();
  if (x < 0 || y < 0 || z < 0
  ||  x >= w || y >= h || z >= d) return;

  int floor = z;
  update(m, m2, ceiling, floor, x, y, z);

  walkUpLeft(m, m2, ceiling, x-1, y-1, floor);
}

void walkUp(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z) {
  int d = m.size();
  int h = m[0].size();
  int w = m[0][0].size();
  if (x < 0 || y < 0 || z < 0
  ||  x >= w || y >= h || z >= d) return;

  int floor = z;
  update(m, m2, ceiling, floor, x, y, z);

  walkUpLeft(m, m2, ceiling, x-1, y-1, floor);
  walkUp(m, m2, ceiling, x, y-1, floor);
  walkUpRight(m, m2, ceiling, x+1, y-1, floor);
}

void walkUpRight(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z) {
  int d = m.size();
  int h = m[0].size();
  int w = m[0][0].size();
  if (x < 0 || y < 0 || z < 0
  ||  x >= w || y >= h || z >= d) return;

  int floor = z;
  update(m, m2, ceiling, floor, x, y, z);

  walkUpRight(m, m2, ceiling, x+1, y-1, floor);
}

void walkRight(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z) {
  int d = m.size();
  int h = m[0].size();
  int w = m[0][0].size();
  if (x < 0 || y < 0 || z < 0
  ||  x >= w || y >= h || z >= d) return;

  int floor = z;
  update(m, m2, ceiling, floor, x, y, z);

  walkUpRight(m, m2, ceiling, x+1, y-1, floor);
  walkRight(m, m2, ceiling, x+1, y, floor);
  walkDownRight(m, m2, ceiling, x+1, y+1, floor);
}

void walkDownRight(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z) {
  int d = m.size();
  int h = m[0].size();
  int w = m[0][0].size();
  if (x < 0 || y < 0 || z < 0
  ||  x >= w || y >= h || z >= d) return;

  int floor = z;
  update(m, m2, ceiling, floor, x, y, z);

  walkDownRight(m, m2, ceiling, x+1, y+1, floor);
}

void walkDonw(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z) {
  int d = m.size();
  int h = m[0].size();
  int w = m[0][0].size();
  if (x < 0 || y < 0 || z < 0
  ||  x >= w || y >= h || z >= d) return;

  int floor = z;
  update(m, m2, ceiling, floor, x, y, z);

  walkDownLeft(m, m2, ceiling, x-1, y+1, floor);
  walkDonw(m, m2, ceiling, x, y+1, floor);
  walkDownRight(m, m2, ceiling, x+1, y+1, floor);
}

void walkDownLeft(std::vector<std::vector<std::vector<int>>> m, Tile& m2, int ceiling, int x, int y, int z) {
  int d = m.size();
  int h = m[0].size();
  int w = m[0][0].size();
  if (x < 0 || y < 0 || z < 0
  ||  x >= w || y >= h || z >= d) return;

  int floor = z;
  update(m, m2, ceiling, floor, x, y, z);

  walkDownLeft(m, m2, ceiling, x-1, y+1, floor);
}

void fillmap(std::vector<std::vector<std::vector<int>>> m, std::vector<int> prota, Tile& m2) {
  int x = prota[0];
  int y = prota[1];
  int z = prota[2];
  int ceiling = z + 1;
  while ((ceiling < m.size()) && (m[ceiling][x][y] == 0)) ceiling++;

  m2.insert(zbe::Point<4>{0, x, y, z});
  m2.insert(zbe::Point<4>{1, x, y, z});
  m2.insert(zbe::Point<4>{2, prota[0], prota[1], prota[2]});

  walkLeft(m, m2, ceiling, x-1, y, z);
  walkUpLeft(m, m2, ceiling, x-1, y-1, z);
  walkUp(m, m2, ceiling, x, y-1, z);
  walkUpRight(m, m2, ceiling, x+1, y-1, z);
  walkRight(m, m2, ceiling, x+1, y, z);
  walkDownRight(m, m2, ceiling, x+1, y+11, z);
  walkDonw(m, m2, ceiling, x, y+1, z);
  walkDownLeft(m, m2, ceiling, x-1, y+1, z);
}

void isometric() {
  const int WIDTH = 1024;
  const int HEIGHT = 768;

  const int MW = 20;
  const int MH = 20;
  const int MD = 10;

  std::vector<int> prota(3, 0);
  prota[0] = 11;
  prota[1] = 12;
  prota[2] = 4;

  std::vector<int> er(MW, 0);
  std::vector<std::vector<int> > layer(MH, er);
  std::vector<std::vector<std::vector<int> > > m(MD, layer);

  Tile m2;
  Tile m3;

  for (int i = 0; i < MH; i++) {
    for (int j = 0; j < MW; j++) {
      m[0][i][j] = 1;
      m[1][i][j] = 1;
    }
  }

  m[1][10][10] = 0;
  m[1][10][11] = 0;
  m[1][10][12] = 0;
  m[1][11][10] = 0;
  m[1][11][11] = 0;
  m[1][11][12] = 0;
  m[1][12][10] = 0;
  m[1][12][11] = 0;
  m[1][12][12] = 0;
  m[1][13][10] = 0;
  m[1][13][11] = 0;
  m[1][13][12] = 0;

  m[2][0][10] = 1;

  printf("Prota: %d, %d, %d\n\n", prota[0], prota[1], prota[2]); fflush(stdout);

  printf("Mapa!\n"); fflush(stdout);
  for (auto &level : m) {
    for (auto &row : level) {
      for (auto &pixel : row) {
        printf("%d ", pixel); fflush(stdout);
      }
      printf("\n"); fflush(stdout);
    }
    printf("\n\n"); fflush(stdout);
  }

  std::shared_ptr<zbe::SDLWindow> window = std::make_shared<zbe::SDLWindow>("isometrico", 100, 100, WIDTH, HEIGHT);
  std::shared_ptr<zbe::SDLImageStore> imgStore(window->getImgStore());

  const char floorfilename[] = "data/images/degryll/isotetris/sueloT.png";
  const char floorfilename2[] = "data/images/degryll/isotetris/sueloG.png";
  const char izqfilename[] = "data/images/degryll/isotetris/izqT.png";
  const char derfilename[] = "data/images/degryll/isotetris/derT.png";
  const char protafilename[] = "data/images/degryll/isotetris/charDT.png";

  uint64_t floortile[2]     = {imgStore->loadImg(floorfilename), imgStore->loadImg(floorfilename2)};
  uint64_t izqtile       = imgStore->loadImg(izqfilename);
  uint64_t dertile       = imgStore->loadImg(derfilename);
  uint64_t protatile     = imgStore->loadImg(protafilename);

  window->setBackgroundColor(64, 0, 0, 0);
  window->clear();

  printf("%s", zbe::SysError::getFirstErrorString().c_str()); fflush(stdout);

  bool l,r,t,b,c,d;
  l = r = t = b = c = d = false;

  SDL_Event event;
  bool keep = true;
  while(keep) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_WINDOWEVENT) {
        switch (event.window.event) {
        case SDL_WINDOWEVENT_CLOSE:
          keep = false;
          break;
        }
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_a:
          l = true;
        break;
        case SDLK_d:
          r = true;
        break;
        case SDLK_w:
          t = true;
        break;
        case SDLK_s:
          b = true;
        break;
        case SDLK_n:
          c = true;
        break;
        case SDLK_m:
          d = true;
        break;
        }

      } else if (event.type == SDL_KEYUP) {
        if (l && SDLK_a) {
          l = false;
          if (prota[0] > 0) prota[0]--;
        }
        if (r && SDLK_d) {
          r = false;
          if (prota[0] < MW-1) prota[0]++;
        }
        if (t && SDLK_w) {
          t = false;
          if (prota[1] > 0) prota[1]--;
        }
        if (b && SDLK_s) {
          b = false;
          if (prota[1] < MH-1) prota[1]++;
        }
        if (c && SDLK_n) {
          c = false;
          if (prota[2] < MD-1) m[prota[2]+1][prota[1]][prota[0]] = 1;
        }
        if (d && SDLK_m) {
          d = false;
          if (prota[2] > 0) m[prota[2]][prota[1]][prota[0]] = 0;
        }

      }  // if SDL_WINDOWEVENT
    }
    window->clear();
    fixposition(prota, m);

    m2.clear();
    for (int i = 0; i < MD; i++) {
      for (int j = 0; j < MH; j++) {
        for (int k = 0; k < MW; k++) {
          if(m[i][j][k] == 1) {
            m2.insert(zbe::Point<4>{0, k, j, i});
            m2.insert(zbe::Point<4>{1, k, j, i});
          }
        }
      }
    }

    m2.insert(zbe::Point<4>{2, prota[0], prota[1], prota[2]});

    m3.clear();
    fillmap(m, prota, m3);
    draw(window, floortile, izqtile, dertile, m, protatile, prota);
    draw2(window, floortile, izqtile, dertile, m, protatile, prota, 550);
    draw3(window, floortile, izqtile, dertile, m2, protatile, prota, 50, 300);
    draw3(window, floortile, izqtile, dertile, m3, protatile, prota, 550, 300);
    if (zbe::SysError::getNErrors() != 0) {
      printf("%s\n", zbe::SysError::getFirstErrorString().c_str()); fflush(stdout);
      zbe::SysError::clear();
    }
    window->present();
  }

}

int degryllmain(int, char*[]) {
  printf("Hola Mundo!\n");

  //vulkantest();
  isometric();

  return (0);
}

//#include "degryllmain.h"
//
//#include <cstdio>
//#include <algorithm>
//
//#include "ZBE/archetypes/Drawable.h"
////#include "ZBE/core/entities/adaptorentities/SimpleSpriteEntity.h"
//#include "ZBE/core/entities/AvatarEntity.h"
//#include "ZBE/core/tools/containers/RsrcStore.h"
//#include "ZBE/core/tools/containers/Ticket.h"
//#include "ZBE/core/tools/containers/TicketedForwardList.h"
//#include "ZBE/core/entities/Adaptor.h"
//#include "ZBE/core/events/EventStore.h"
//#include "ZBE/core/events/generators/InputEventGenerator.h"
////#include "ZBE/core/events/generators/CollisionEventGenerator.h"
//#include "ZBE/core/events/generators/TimeEventGenerator.h"
//#include "ZBE/SDL/tools/SDLTimer.h"
//#include "ZBE/SDL/system/SDLEventDispatcher.h"
//#include "ZBE/core/system/SysTime.h"
//#include "ZBE/SDL/system/SDLWindow.h"
//#include "ZBE/SDL/drawers/SingleSpriteSDLDrawer.h"
//#include "ZBE/core/daemons/DaemonMaster.h"
//#include "ZBE/core/daemons/Punishers.h"
//#include "ZBE/entities/adaptors/SimpleDrawableSingleSpriteAdaptor.h"
//
//#include "game/events/handlers/ExitInputHandler.h"
//
//class GameReactor {};
//
//////namespace zbetris {
//////
//////class Block: public zbe::Drawable,
//////             public zbe::AvatarEntityAdapted<zbe::SingleSprite> {
//////public:
//////  Block() : x(0), y(0), t(0), lm(zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite >*> >::getInstance()), ticket(nullptr) {}
//////  Block(int64_t x, int64_t y, uint64_t t, uint64_t id) : x(x), y(y), t(t), lm(zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite>*> >::getInstance()), ticket(lm.get(id)->push_front(this)) {}
//////
//////  void addTo(uint64_t id) {
//////    ticket = lm.get(id)->push_front(this);
//////  }
//////
//////  void setX(int64_t x) {this->x = x;}
//////  void setY(int64_t y) {this->y = y;}
//////  void setXY(int64_t x, int64_t y) {this->x = x; this->y = y;}
//////  void setType(int64_t type) {this->t = type;}
//////
//////  int64_t getX() {return (x);}
//////  int64_t getY() {return (y);}
//////  int64_t getW() {return (1);}
//////  int64_t getH() {return (1);}
//////  uint64_t getGraphics() {return (t);}
//////
//////  void setVisible()   {ticket->setACTIVE();}    //!< The block will be visible.
//////  void setInvisible() {ticket->setINACTIVE();}  //!< The block will be invisible.
//////  void setERASED()    {ticket->setERASED();}    //!< The block won't be used anymore.
//////
//////private:
//////  int64_t x;
//////  int64_t y;
//////  uint64_t t;
//////  zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite>*> >& lm;
//////  std::shared_ptr<zbe::TicketedElement<zbe::AvatarEntity<zbe::SingleSprite>*> > ticket;
//////};
//////
//////class SimpleDrawableBoardSpriteAdaptor : public zbe::Adaptor<zbe::SingleSprite> {
//////public:
//////  SimpleDrawableBoardSpriteAdaptor(const SimpleDrawableBoardSpriteAdaptor&) = delete;
//////  void operator=(const SimpleDrawableBoardSpriteAdaptor&) = delete;
//////
//////  SimpleDrawableBoardSpriteAdaptor(int topLeftX, int topLeftY, int tileW, int tileH, zbe::Drawable* entity) : x(topLeftX), y(topLeftY), w(tileW), h(tileH), e(entity), s(nullptr) {}
//////
//////  virtual ~SimpleDrawableBoardSpriteAdaptor() {
//////    delete s;
//////  }
//////
//////  zbe::SingleSprite* getAvatar() {
//////    delete s;
//////    s = new zbe::SingleSprite();
//////
//////    s->x = e->getX() * w + x;
//////    s->y = e->getY() * w + y;
//////    s->w = w;
//////    s->h = h;
//////    s->graphics = e->getGraphics();
//////
//////    return (s);
//////  }
//////
//////private:
//////  int64_t x;
//////  int64_t y;
//////  int64_t w;
//////  int64_t h;
//////  zbe::Drawable* e;
//////  zbe::SingleSprite* s;
//////};
//////
//////class Board {
//////public:
//////  Board(int width, int height, uint64_t t, uint64_t id) : w(width), h(height), b(new int[w*h]), bb(new Block[w*h]()), lines(0) {
//////    for(int i = 0; i < height; i++) {
//////      for(int j = 0; j < width; j++) {
//////        b[i*width+j] = 0;
//////        bb[i*width+j].addTo(id);
//////        bb[i*width+j].setX(j);
//////        bb[i*width+j].setY(i);
//////        bb[i*width+j].setType(t);
//////        bb[i*width+j].setInvisible();
//////
//////
//////        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor = std::make_shared<zbetris::SimpleDrawableBoardSpriteAdaptor>(100, 100, 32, 32, bb + (i*width+j));
//////        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(bb + (i*width+j)))->setAdaptor(spriteAdaptor);
//////      }
//////    }
//////  }
//////
//////  void setValue(int x, int y, uint64_t t) {
//////    b[y*w+x] = t;
//////    if(t) bb[y*w+x].setVisible();
//////    else bb[y*w+x].setInvisible();
//////  }
//////
//////  void setTile(int x, int y, uint64_t t) {
//////    setValue(x, y, t);
//////  }
//////
//////  bool isOcupied(int x, int y) {
//////    if((x < 0) || (x >= w) || (y < 0) || (y >= h)) return (true);
//////
//////    return (b[y*w+x]);
//////  }
//////
//////  void occupy(int x, int y) {
//////    if((x < 0) || (x >= w) || (y < 0) || (y >= h)) return;
//////
//////    setTile(x, y, 1);
//////  }
//////
//////  void check() {
//////    for(int i = h-1; i >= 0; i--) {
//////        int o = 0;
//////      for(int j = 0; j < w; j++) {
//////        o += b[i*w+j];
//////      }
//////      if (o == w) {
//////        lines++;
//////        if(lines > 9) {apaga(); return;}
//////        printf("lines: %d\n", lines);
//////        for(int k = i; k > 0; k--) {
//////          for(int l = 0; l < w; l++) {
//////            setValue(l, k, b[(k-1)*w+l]);
//////          }
//////        }
//////        for(int l = 0; l < w; l++) {
//////          b[l] = 0;
//////        }
//////        i++;
//////      }
//////    }
//////  }
//////
//////
//////  void setLines(int lines) {this->lines = lines;}
//////  int getLines() {return (lines);}
//////
//////  void apaga() {
//////    for(int i = 0; i < h; i++) {
//////      for(int j = 0; j < w; j++) {
//////        bb[i*w+j].setInvisible();
//////      }
//////    }
//////  }
//////
//////private:
//////  int w;
//////  int h;
//////  int *b;
//////  Block* bb;
//////  int lines;
//////};
//////
//////class Tetromino {
//////public:
//////  enum TetrominoType {
//////    PALO     = 1,
//////    CUADRADO = 2,
//////    Z        = 3,
//////    S        = 4,
//////    T        = 5,
//////    L        = 6,
//////    Linv     = 7
//////  };
//////
//////  Tetromino(uint64_t img, uint64_t id, Board& board, int type = 0) : b(), x(5), y(3), t(type), r(0), board(board) {
//////    for(uint64_t i = 0; i < 4; i++) {
//////      b[i].addTo(id);
//////      //b[i].setType(type);
//////      std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor = std::make_shared<zbetris::SimpleDrawableBoardSpriteAdaptor>(100, 100, 32, 32, b + i);
//////      ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(b + i))->setAdaptor(spriteAdaptor);
//////      b[i].setType(img);
//////
//////      if(t) b[i].setVisible();
//////      else b[i].setInvisible();
//////    }
//////
//////    setType(type);
//////  }
//////
//////  void setType(int type, int rotation = 0) {
//////    if(!isOcupied(x, y, type, rotation)) {
//////      this->t = type;
//////      this->r = rotation;
//////      setPosition();
//////    }
////////    this->t = type;
////////    this->r = rotation;
////////    setPosition();
////////    switch (type) {
////////    case PALO:     setPalo(); break;
////////    case CUADRADO: setCuadrado(); break;
////////    case Z:        setZ(); break;
////////    case S:        setS(); break;
////////    case T:        setT(); break;
////////    case L:        setL(); break;
////////    case Linv:     setLinv(); break;
////////    default:       setInvisible();
////////    }
//////  }
//////
//////  void rotateLeft()  {
//////    int newr = (r+1) % 4;
//////    if(!isOcupied(x, y, t, newr)) {
//////      r = newr;
//////      setPosition();
//////    }
//////  }
//////  //void rotateLeft()  {setType(t, (r+1)%4);}
//////  //void rotateRight() {setType(t, (r-1)%4);}
//////
//////  void drop() {
//////    if(!isOcupied(x, y+1, t, r)) {
//////      y++;
//////      setPosition();
//////    } else {
//////      occupy(x, y, t, r);
//////      if (board.getLines() > 9) {
//////        for(uint64_t i = 0; i < 4; i++) {
//////          b[i].setInvisible();
//////        }
//////      } else {
//////      x = 5;
//////      y = 3;
//////      //t = (t+1) % 8;
//////      t = (rand() % 7) + 1;
//////      setPosition();
//////      }
//////    }
//////  }
//////
//////  void move(int offset) {
//////    if(!isOcupied(x+offset, y, t, r)) {
//////      x += offset,
//////      setPosition();
//////    }
//////  }
//////
//////private:
//////
//////  void setPosition() {
//////    for(uint64_t i = 0; i < 4; i++) {
//////      if (t) {
//////        b[i].setVisible();
//////        b[i].setXY(x+offsets[t-1][r][i][0], y+offsets[t-1][r][i][1]);
//////      } else {
//////        b[i].setInvisible();
//////      }
//////    }
//////  }
//////
//////  bool isOcupied(int x, int y, int type, int rotation) {
//////    return ( board.isOcupied(x+offsets[type-1][rotation][0][0], y+offsets[type-1][rotation][0][1])
//////          || board.isOcupied(x+offsets[type-1][rotation][1][0], y+offsets[type-1][rotation][1][1])
//////          || board.isOcupied(x+offsets[type-1][rotation][2][0], y+offsets[type-1][rotation][2][1])
//////          || board.isOcupied(x+offsets[type-1][rotation][3][0], y+offsets[type-1][rotation][3][1]));
//////  }
//////
//////  void occupy(int x, int y, int type, int rotation) {
//////    board.occupy(x+offsets[type-1][rotation][0][0], y+offsets[type-1][rotation][0][1]);
//////    board.occupy(x+offsets[type-1][rotation][1][0], y+offsets[type-1][rotation][1][1]);
//////    board.occupy(x+offsets[type-1][rotation][2][0], y+offsets[type-1][rotation][2][1]);
//////    board.occupy(x+offsets[type-1][rotation][3][0], y+offsets[type-1][rotation][3][1]);
//////    board.check();
//////  }
//////
//////  void setInvisible() {
//////    for(uint64_t i = 0; i < 4; i++) {
//////      b[i].setInvisible();
//////    }
//////  }
//////
//////  static int offsets[7][4][4][2];
//////  Block b[4];
//////  int x, y;
//////  int t;
//////  int r;
//////  Board& board;
//////};
//////
//////int Tetromino::offsets[7][4][4][2] = {{ {{ -2,  0 }, { -1,  0 }, {  0,  0 }, { +1,  0 }}, {{  0, -2 }, {  0, -1 }, {  0,  0 }, {  0, +1 }}, {{ -2,  0 }, { -1,  0 }, {  0,  0 }, { +1,  0 }}, {{  0, -2 }, {  0, -1 }, {  0,  0 }, {  0, +1 }} },
//////                                      { {{  0, -1 }, { +1, -1 }, {  0,  0 }, { +1,  0 }}, {{  0, -1 }, { +1, -1 }, {  0,  0 }, { +1,  0 }}, {{  0, -1 }, { +1, -1 }, {  0,  0 }, { +1,  0 }}, {{  0, -1 }, { +1, -1 }, {  0,  0 }, { +1,  0 }} },
//////                                      { {{  0, -1 }, { -1, -1 }, {  0,  0 }, { +1,  0 }}, {{ +1, -1 }, { +1,  0 }, {  0,  0 }, {  0, +1 }}, {{  0, -1 }, { -1, -1 }, {  0,  0 }, { +1,  0 }}, {{ +1, -1 }, { +1,  0 }, {  0,  0 }, {  0, +1 }} },
//////                                      { {{  0, -1 }, { +1, -1 }, {  0,  0 }, { -1,  0 }}, {{ -1, -1 }, { -1,  0 }, {  0,  0 }, {  0, +1 }}, {{  0, -1 }, { +1, -1 }, {  0,  0 }, { -1,  0 }}, {{ -1, -1 }, { -1,  0 }, {  0,  0 }, {  0, +1 }} },
//////                                      { {{  0, -1 }, { -1,  0 }, {  0,  0 }, { +1,  0 }}, {{ -1,  0 }, {  0, +1 }, {  0,  0 }, {  0, -1 }}, {{  0, +1 }, { -1,  0 }, {  0,  0 }, { +1,  0 }}, {{ +1,  0 }, {  0, -1 }, {  0,  0 }, {  0, +1 }} },
//////                                      { {{  0, -2 }, {  0, -1 }, {  0,  0 }, { +1,  0 }}, {{ -2,  0 }, { -1,  0 }, {  0,  0 }, {  0, -1 }}, {{  0, +2 }, {  0, +1 }, {  0,  0 }, { -1,  0 }}, {{ +2,  0 }, { +1,  0 }, {  0,  0 }, {  0, +1 }} },
//////                                      { {{  0, -2 }, {  0, -1 }, {  0,  0 }, { -1,  0 }}, {{ -2,  0 }, { -1,  0 }, {  0,  0 }, {  0, +1 }}, {{  0, +2 }, {  0, +1 }, {  0,  0 }, { +1,  0 }}, {{ +2,  0 }, { +1,  0 }, {  0,  0 }, {  0, -1 }} }};
//////
//////class MoveLeftInputHandler : public zbe::InputHandler {
//////	public:
//////	  MoveLeftInputHandler(const MoveLeftInputHandler&) = delete;
//////	  void operator=(const MoveLeftInputHandler&) = delete;
//////
//////  	MoveLeftInputHandler(Tetromino& tetromino) : t(tetromino) {}
//////
//////  	void run(float status) {
//////      if( status) {
//////          t.move(-1);
//////      }
//////  	}
//////
//////	private:
//////    Tetromino& t;
//////};
//////
//////class MoveRightInputHandler : public zbe::InputHandler {
//////	public:
//////	  MoveRightInputHandler(const MoveRightInputHandler&) = delete;
//////	  void operator=(const MoveRightInputHandler&) = delete;
//////
//////  	MoveRightInputHandler(Tetromino& tetromino) : t(tetromino) {}
//////
//////  	void run(float status) {
//////      if( status) {
//////          t.move(+1);
//////      }
//////  	}
//////
//////	private:
//////    Tetromino& t;
//////};
//////
//////class RotateLeftInputHandler : public zbe::InputHandler {
//////	public:
//////	  RotateLeftInputHandler(const RotateLeftInputHandler&) = delete;
//////	  void operator=(const RotateLeftInputHandler&) = delete;
//////
//////  	RotateLeftInputHandler(Tetromino& tetromino) : t(tetromino) {}
//////
//////  	void run(float status) {
//////      if( status) {
//////          t.rotateLeft();
//////      }
//////  	}
//////
//////	private:
//////    Tetromino& t;
//////};
////
//////}  // namespace zbe
//////
//////namespace isolux {
//////
//////class Mitil : public zbe::Drawable,
//////              public zbe::AvatarEntityAdapted<zbe::SingleSprite> {
//////public:
//////  Mitil(int x, int y, int width, int height, int graphics, uint64_t id)
//////  : x(x), y(y), w(width), h(height), g(graphics),
//////    lm(zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite>*> >::getInstance()),
//////    ticket(lm.get(id)->push_front(this)) {}
//////
////////  void setData(int x, int y, int width, int height, int graphics) {
////////    this.x = x;
////////    this.y = y;
////////    this.w = width;
////////    this.h = height;
////////    this.g = graphics;
////////  }
//////
//////  void setX(int x) {this->x = x;}
//////  void setY(int y) {this->y = y;}
//////  void setW(int w) {this->w = w;}
//////  void setH(int h) {this->h = h;}
//////  void setG(int g) {this->g = g;}
//////
//////  int64_t getX() {return (x);}
//////  int64_t getY() {return (y);}
//////  int64_t getW() {return (w);}
//////  int64_t getH() {return (h);}
//////  uint64_t getGraphics() {return (g);}
//////
//////  void setVisible()   {ticket->setACTIVE();}    //!< The block will be visible.
//////  void setInvisible() {ticket->setINACTIVE();}  //!< The block will be invisible.
//////  void setERASED()    {ticket->setERASED();}    //!< The block won't be used anymore.
//////
//////private:
//////  int x;
//////  int y;
//////  int w;
//////  int h;
//////  int g;
//////  zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite>*> >& lm;
//////  std::shared_ptr<zbe::TicketedElement<zbe::AvatarEntity<zbe::SingleSprite>*> > ticket;
//////};
//////
//////class MiMap {
//////public:
//////  MiMap(const MiMap&) = delete;
//////  void operator=(const MiMap&) = delete;
//////
//////  MiMap(int x, int y, int width, int height, int levels, int *mapa, int tileWidth, int tileHeight, int g, uint64_t id)
//////  : x(x), y(y), width(width), height(height), levels(levels), tileWidth(tileWidth), tileHeight(tileHeight),
//////    g(g), id(id), hw(tileWidth/2), hh(tileHeight/2), lvl(height*width), cx(30), cy(22), isActive(false),
//////    mapa(mapa), m(width * height, nullptr), s0(width * height, nullptr),
//////    i1(width * height, nullptr), d1(width * height, nullptr), s1(width * height, nullptr),
//////    i2(width * height, nullptr), d2(width * height, nullptr), s2(width * height, nullptr),
//////    i3(width * height, nullptr), d3(width * height, nullptr), s3(width * height, nullptr),
//////    i4(width * height, nullptr), d4(width * height, nullptr), s4(width * height, nullptr),
//////    arcade(nullptr), character(nullptr), musica(nullptr), muros(nullptr) {
//////
//////    create();
//////  }
//////
//////  void create() {
//////    arcade = new Mitil(x + 31 * tileWidth - 7, y + 21 * hh - 38, 26, 47, g+7, id);
//////    std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptorArcade = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(arcade);
//////    ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(arcade))->setAdaptor(spriteAdaptorArcade);
//////
//////    arcade->setInvisible();
//////
//////    character = new Mitil(x + cx * tileWidth + 4, y + cy * hh - 31, 11, 38, g+3, id);
//////    std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptorChar = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(character);
//////    ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(character))->setAdaptor(spriteAdaptorChar);
//////
//////    character->setInvisible();
//////
//////    musica = new Mitil(x, y + 300, 673, 271, g+8, id);
//////    std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptormusica = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(musica);
//////    ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(musica))->setAdaptor(spriteAdaptormusica);
//////
//////    musica->setInvisible();
//////
//////    muros = new Mitil(x, y + 300, 673, 271, g+9, id);
//////    std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptormuros = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(muros);
//////    ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(muros))->setAdaptor(spriteAdaptormuros);
//////
//////    muros->setInvisible();
//////
//////
//////    for(int i = 0; i < height; i++) {
//////      int offset = (i % 2) ? hw : 0;
//////      for(int j = 0; j < width; j++) {
//////        s4[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 9 - 9 - 9 - 9, tileWidth, tileHeight, g, id);
//////        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor14 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(s4[i*width+j]);
//////        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(s4[i*width+j]))->setAdaptor(spriteAdaptor14);
//////        s4[i * width + j]->setInvisible();
//////      }
//////    }
//////
//////    for(int i = height-1; i >= 0; i--) {
//////      int offset = (i % 2) ? hw : 0;
//////      for(int j = width-1; j >= 0; j--) {
//////        d4[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 5 - 9 - 9 - 9, 8, 14, g+1, id);
//////        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor13 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(d4[i*width+j]);
//////        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(d4[i*width+j]))->setAdaptor(spriteAdaptor13);
//////
//////        i4[i * width + j] = new Mitil(x + j * tileWidth + offset+8, y + i * hh - 5 - 9 - 9 - 9, 8, 14, g+2, id);
//////        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor12 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(i4[i*width+j]);
//////        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(i4[i*width+j]))->setAdaptor(spriteAdaptor12);
//////        d4[i * width + j]->setInvisible();
//////        i4[i * width + j]->setInvisible();
//////      }
//////    }
//////
//////    for(int i = 0; i < height; i++) {
//////      int offset = (i % 2) ? hw : 0;
//////      for(int j = 0; j < width; j++) {
//////        s3[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 9 - 9 - 9, tileWidth, tileHeight, g, id);
//////        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor11 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(s3[i*width+j]);
//////        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(s3[i*width+j]))->setAdaptor(spriteAdaptor11);
//////        s3[i * width + j]->setInvisible();
//////      }
//////    }
//////
//////    for(int i = height-1; i >= 0; i--) {
//////      int offset = (i % 2) ? hw : 0;
//////      for(int j = width-1; j >= 0; j--) {
//////        d3[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 5 - 9 - 9, 8, 14, g+1, id);
//////        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor10 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(d3[i*width+j]);
//////        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(d3[i*width+j]))->setAdaptor(spriteAdaptor10);
//////
//////        i3[i * width + j] = new Mitil(x + j * tileWidth + offset+8, y + i * hh - 5 - 9 - 9, 8, 14, g+2, id);
//////        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor9 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(i3[i*width+j]);
//////        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(i3[i*width+j]))->setAdaptor(spriteAdaptor9);
//////        d3[i * width + j]->setInvisible();
//////        i3[i * width + j]->setInvisible();
//////      }
//////    }
//////
//////    for(int i = 0; i < height; i++) {
//////      int offset = (i % 2) ? hw : 0;
//////      for(int j = 0; j < width; j++) {
//////        s2[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 9 - 9, tileWidth, tileHeight, g, id);
//////        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor8 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(s2[i*width+j]);
//////        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(s2[i*width+j]))->setAdaptor(spriteAdaptor8);
//////        s2[i * width + j]->setInvisible();
//////      }
//////    }
//////
//////    for(int i = height-1; i >= 0; i--) {
//////      int offset = (i % 2) ? hw : 0;
//////      for(int j = width-1; j >= 0; j--) {
//////        d2[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 5 - 9, 8, 14, g+1, id);
//////        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor7 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(d2[i*width+j]);
//////        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(d2[i*width+j]))->setAdaptor(spriteAdaptor7);
//////
//////        i2[i * width + j] = new Mitil(x + j * tileWidth + offset+8, y + i * hh - 5 - 9, 8, 14, g+2, id);
//////        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor6 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(i2[i*width+j]);
//////        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(i2[i*width+j]))->setAdaptor(spriteAdaptor6);
//////        d2[i * width + j]->setInvisible();
//////        i2[i * width + j]->setInvisible();
//////      }
//////    }
//////
//////    for(int i = 0; i < height; i++) {
//////      int offset = (i % 2) ? hw : 0;
//////      for(int j = 0; j < width; j++) {
//////        s1[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 9, tileWidth, tileHeight, g, id);
//////        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor5 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(s1[i*width+j]);
//////        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(s1[i*width+j]))->setAdaptor(spriteAdaptor5);
//////        s1[i * width + j]->setInvisible();
//////      }
//////    }
//////
//////    for(int i = height-1; i >= 0; i--) {
//////      int offset = (i % 2) ? hw : 0;
//////      for(int j = width-1; j >= 0; j--) {
//////        d1[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh - 5, 8, 14, g+1, id);
//////        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor4 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(d1[i*width+j]);
//////        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(d1[i*width+j]))->setAdaptor(spriteAdaptor4);
//////
//////        i1[i * width + j] = new Mitil(x + j * tileWidth + offset+8, y + i * hh - 5, 8, 14, g+2, id);
//////        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor3 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(i1[i*width+j]);
//////        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(i1[i*width+j]))->setAdaptor(spriteAdaptor3);
//////        d1[i * width + j]->setInvisible();
//////        i1[i * width + j]->setInvisible();
//////      }
//////    }
//////
//////    for(int i = 0; i < height; i++) {
//////      int offset = (i % 2) ? hw : 0;
//////      for(int j = 0; j < width; j++) {
//////        s0[i * width + j] = new Mitil(x + j * tileWidth + offset, y + i * hh, tileWidth, tileHeight, g, id);
//////        std::shared_ptr<zbe::Adaptor<zbe::SingleSprite> > spriteAdaptor2 = std::make_shared<zbe::SimpleDrawableSingleSpriteAdaptor>(s0[i*width+j]);
//////        ((zbe::AvatarEntityAdapted<zbe::SingleSprite>*)(s0[i*width+j]))->setAdaptor(spriteAdaptor2);
//////        s0[i * width + j]->setInvisible();
//////      }
//////    }
//////  }
//////
//////  void activate() {
//////    isActive = true;
//////    arcade->setVisible();
//////    character->setVisible();
//////    musica->setVisible();
//////
//////    for(int i = 0; i < height; i++) {
//////      for(int j = 0; j < width; j++) {
//////        if (mapa[lvl*3 + i*width+j] != 0) {
//////            s4[i * width + j]->setVisible();
//////        }
//////      }
//////    }
//////
//////    for(int i = height-1; i >= 0; i--) {
//////      for(int j = width-1; j >= 0; j--) {
//////        if (mapa[lvl*3 + i*width+j] != 0) {
//////            d4[i * width + j]->setVisible();
//////            i4[i * width + j]->setVisible();
//////        }
//////      }
//////    }
//////
//////    for(int i = 0; i < height; i++) {
//////      for(int j = 0; j < width; j++) {
//////        if (mapa[lvl*2 + i*width+j] == 0) {
//////            s3[i * width + j]->setInvisible();
//////        }
//////      }
//////    }
//////
//////    for(int i = height-1; i >= 0; i--) {
//////      for(int j = width-1; j >= 0; j--) {
//////        if (mapa[lvl*2 + i*width+j] != 0) {
//////            d3[i * width + j]->setVisible();
//////            i3[i * width + j]->setVisible();
//////        }
//////      }
//////    }
//////
//////    for(int i = 0; i < height; i++) {
//////      for(int j = 0; j < width; j++) {
//////        if (mapa[lvl + i*width+j] != 0) {
//////            s2[i * width + j]->setVisible();
//////        }
//////      }
//////    }
//////
//////    for(int i = height-1; i >= 0; i--) {
//////      for(int j = width-1; j >= 0; j--) {
//////        if (mapa[lvl + i*width+j] != 0) {
//////            d2[i * width + j]->setVisible();
//////            i2[i * width + j]->setVisible();
//////        }
//////      }
//////    }
//////
//////    for(int i = 0; i < height; i++) {
//////      for(int j = 0; j < width; j++) {
//////        if (mapa[i*width+j] != 0) {
//////            s1[i * width + j]->setVisible();
//////        }
//////      }
//////    }
//////
//////    for(int i = height-1; i >= 0; i--) {
//////      for(int j = width-1; j >= 0; j--) {
//////        if (mapa[i*width+j] != 0) {
//////            d1[i * width + j]->setVisible();
//////            i1[i * width + j]->setVisible();
//////        }
//////      }
//////    }
//////
//////    for(int i = 0; i < height; i++) {
//////      for(int j = 0; j < width; j++) {
//////          s0[i * width + j]->setVisible();
//////      }
//////    }
//////  }
//////
//////  void setCharPos(int g) {
//////    int offset = (cy % 2) ? hw : 0;
//////    character->setX(x + cx * tileWidth + offset + 4);
//////    character->setY(y + cy * hh - 31);
//////    character->setG(g);
//////
//////    if ((cx == 30) && cy == 22) {
//////      musica->setVisible();
//////    } else {
//////      musica->setInvisible();
//////    }
//////
//////    if (cy > 38) {
//////      muros->setVisible();
//////    } else if ((cx < 7) && (cy < 30)) {
//////      muros->setVisible();
//////    } else {
//////      muros->setInvisible();
//////    }
//////  }
//////
//////  void movecu() {
//////    if (!isActive) return;
//////    if(cy % 2) {
//////      if (mapa[(cy-1)*width+(cx+1)] == 0) {cy--; cx++;}
//////    } else {
//////      if (mapa[(cy-1)*width+cx] == 0) {cy--;}
//////    }
//////    setCharPos(g+3);
//////  }
//////
//////  void movecd() {
//////    if (!isActive) return;
//////    if(cy % 2) {
//////      if (mapa[(cy+1)*width+cx] == 0) {cy++;}
//////    } else {
//////      if (mapa[(cy+1)*width+(cx-1)] == 0) {cy++; cx--;}
//////    }
//////    setCharPos(g+4);
//////  }
//////
//////  void movecl() {
//////    if (!isActive) return;
//////    if(cy % 2) {
//////      if (mapa[(cy-1)*width+cx] == 0) {cy--;}
//////    } else {
//////      if (mapa[(cy-1)*width+(cx-1)] == 0) {cy--; cx--;}
//////    }
//////    setCharPos(g+5);
//////  }
//////
//////  void movecr() {
//////    if (!isActive) return;
//////    if(cy % 2) {
//////      if (mapa[(cy+1)*width+(cx+1)] == 0) {cy++; cx++;}
//////    } else {
//////      if (mapa[(cy+1)*width+cx] == 0) {cy++;}
//////    }
//////    setCharPos(g+6);
//////  }
//////
//////private:
//////  int x;
//////  int y;
//////  int width;
//////  int height;
//////  int levels;
//////  int tileWidth;
//////  int tileHeight;
//////  int g;
//////  uint64_t id;
//////  int hw;
//////  int hh;
//////  int lvl;
//////  int cx;
//////  int cy;
//////  bool isActive;
//////  int *mapa;
//////  std::vector<Mitil*> m;
//////  std::vector<Mitil*> s0;
//////  std::vector<Mitil*> i1;
//////  std::vector<Mitil*> d1;
//////  std::vector<Mitil*> s1;
//////  std::vector<Mitil*> i2;
//////  std::vector<Mitil*> d2;
//////  std::vector<Mitil*> s2;
//////  std::vector<Mitil*> i3;
//////  std::vector<Mitil*> d3;
//////  std::vector<Mitil*> s3;
//////  std::vector<Mitil*> i4;
//////  std::vector<Mitil*> d4;
//////  std::vector<Mitil*> s4;
//////  Mitil* arcade;
//////  Mitil* character;
//////  Mitil* musica;
//////  Mitil* muros;
//////};
//////
//////class MoveCUInputHandler : public zbe::InputHandler {
//////	public:
//////	  MoveCUInputHandler(const MoveCUInputHandler&) = delete;
//////	  void operator=(const MoveCUInputHandler&) = delete;
//////
//////  	MoveCUInputHandler(MiMap& mapa) : m(mapa) {}
//////
//////  	void run(float status) {
//////      if( status) {
//////          m.movecu();
//////      }
//////  	}
//////
//////	private:
//////    MiMap& m;
//////};
//////
//////class MoveCDInputHandler : public zbe::InputHandler {
//////	public:
//////	  MoveCDInputHandler(const MoveCDInputHandler&) = delete;
//////	  void operator=(const MoveCDInputHandler&) = delete;
//////
//////  	MoveCDInputHandler(MiMap& mapa) : m(mapa) {}
//////
//////  	void run(float status) {
//////      if( status) {
//////          m.movecd();
//////      }
//////  	}
//////
//////	private:
//////    MiMap& m;
//////};
//////
//////class MoveCLInputHandler : public zbe::InputHandler {
//////	public:
//////	  MoveCLInputHandler(const MoveCLInputHandler&) = delete;
//////	  void operator=(const MoveCLInputHandler&) = delete;
//////
//////  	MoveCLInputHandler(MiMap& mapa) : m(mapa) {}
//////
//////  	void run(float status) {
//////      if( status) {
//////          m.movecl();
//////      }
//////  	}
//////
//////	private:
//////    MiMap& m;
//////};
//////
//////class MoveCRInputHandler : public zbe::InputHandler {
//////	public:
//////	  MoveCRInputHandler(const MoveCRInputHandler&) = delete;
//////	  void operator=(const MoveCRInputHandler&) = delete;
//////
//////  	MoveCRInputHandler(MiMap& mapa) : m(mapa) {}
//////
//////  	void run(float status) {
//////      if( status) {
//////          m.movecr();
//////      }
//////  	}
//////
//////	private:
//////    MiMap& m;
//////};
//////
//////}  // namespace isolux
//////
////void loadMap(const char* filename, int** m, int& w, int& h, int& l) {
////  FILE *f = fopen(filename, "r");
////  fscanf(f, "%d %d %d", &w, &h, &l);
////  printf("mapa: %d %d %d\n", w, h, l);
////  *m = (int*)malloc(sizeof(int) * w * h * l);
////  int *p = *m;
////  int idx = 0;
////  int aux;
////  for(int k = 0; k < l; k++) {
////    for(int i = 0; i < h; i++) {
////      for(int j = 0; j < w; j++) {
////        fscanf(f, "%d ", &aux);
////        idx++;
////        p[0] = aux;
////        p++;
////      }
////    }
////  }
////
////  fclose(f);
////}
////
//////void printMap(int* m, int w, int h, int l) {
//////  int *p = m;
//////  for(int k = 0; k < l; k++) {
//////    for(int i = 0; i < h; i++) {
//////      for(int j = 0; j < w; j++) {
//////          printf("%d", p[0]);
//////          p++;
//////      }
//////      printf("\n");
//////    }
//////    printf("--------------------------------------------------\n");
//////  }
//////}
////
////class MultiLevelMap {
////public:
////  MultiLevelMap(const MultiLevelMap&) = delete;
////  void operator=(const MultiLevelMap&) = delete;
////
////  MultiLevelMap(int width, int height, int depth) : m(new int[width*height*depth]), w(width), h(height), d(depth), hw(w/2), hh(h/2), hd(d/2) {}
////  MultiLevelMap(int width, int height, int depth, int* map) : m(new int[width*height*depth]), w(width), h(height), d(depth), hw(w/2), hh(h/2), hd(d/2) {
////    std::copy(map, map + (w*h*d), m);
////  }
////
////  void setTile(int width, int height, int depth, int value) {m[(height * w + width) * d + depth] = value;}
////
////  int getTile(int width, int height, int depth) {return (m[(height * w + width) * d + depth]);}
////  int getTile(int position) {return (m[position]);}
////
////  int getW() {return (w);}
////  int getH() {return (h);}
////  int getD() {return (d);}
////  int getHW() {return (hw);}
////  int getHH() {return (hh);}
////  int getHD() {return (hd);}
////
////private:
////  int *m;
////  int w, h, d;
////  int hw, hh, hd;
////};
////
////struct TileComparator {
////  bool operator() (const zbe::Point<3>& lhs, const zbe::Point<3>& rhs) const {
////    if (lhs[3] < rhs[3]) {return true;}
////    else if (lhs[3] > rhs[3]) {return false;}
////
////    if (lhs[2] < rhs[2]) {return true;}
////    else if (lhs[2] > rhs[2]) {return false;}
////
////    if (lhs[1] < rhs[1]) {return true;}
////    else if (lhs[1] > rhs[1]) {return false;}
////
////    return false;
////  }
////};
////
////
////class IsometricDrawer {
////public:
////  IsometricDrawer(const IsometricDrawer&) = delete;
////  void operator=(const IsometricDrawer&) = delete;
////
////  IsometricDrawer(MultiLevelMap* map, uint64_t groundImage, uint64_t lWallImage, uint64_t rWallImage, zbe::SDLWindow* window)
////  : m(map), grimage(groundImage), lwimage(lWallImage), rwimage(rWallImage), ground(), leftWall(), rightWall(), window(window) {}
////
////  void setMap(MultiLevelMap* map) {m = map;}
////
////  void draw();
////
////private:
////  MultiLevelMap* m;
////  uint64_t grimage;
////  uint64_t lwimage;
////  uint64_t rwimage;
////  std::set<zbe::Point<3>, TileComparator> ground;
////  std::set<zbe::Point<3>, TileComparator> leftWall;
////  std::set<zbe::Point<3>, TileComparator> rightWall;
////  zbe::SDLWindow* window;
////};
////
//////void draw() {
//////  int x = m->getHW();
//////  int y = m->getHH();
//////  int z = m->getHD();
//////
//////  int k = z;
//////
//////  while((k > 0) && m->getTile(x, y, k) == 0) k--;
//////  while((k < (m->getD()-1)) && m->getTile(x, y, k) == 1) k++;
//////  int ground = k;
//////
//////  floors.insert({(double)x, (double)y, (double)k});
//////
//////  while((k < (m->getD()-1)) && m->getTile(x, y, k) == 0) k++;
//////  int ceiling = k;
//////
//////  walkUp();
//////  walkUpRight();
//////  walkRight();
//////  walkDownRight();
//////  walkDonw();
//////  walkDownLeft();
//////  walkLeft();
//////  walkUpLeft();
//////}
//////
//////findWalls(int x, int y, int z) {
//////  if((y % 2) == 0) {
//////    // leftWall only if (X , Y) is at the right:
//////    //   - Take Y and go up to a even number, ie. (3 -> 2) or (-3 -> 4)
//////    //   - subtract X - (Y/2) if thats is greater or equals to 1, draw the wall.
//////    if (m->getTile(x-1, y+1, k) == 0) {leftWall.insert({(double)x, (double)y, (double)z});}
//////    if (m->getTile(x,   y+1, k) == 0) {rightWall.insert({(double)x, (double)y, (double)z});}
//////  } else {
//////    if (m->getTile(x,   y+1, k) == 0) {leftWall.insert({(double)x, (double)y, (double)z});}
//////    if (m->getTile(x+1, y+1, k) == 0) {rightWall.insert({(double)x, (double)y, (double)z});}
//////  }
//////}
//////
//////int findFloors(int x, int y, int z, int ceiling) {
//////  int k = z;
//////  while((k > 0) && m->getTile(x, y, k) == 0) k--;
//////  while((k < ceiling) && m->getTile(x, y, k) == 1) findWalls(x, y, k++);
//////  int ground = k;
//////  if(ground < ceiling) {
//////    floors.insert({(double)x, (double)y, (double)k});
//////  }
//////
//////  while (k < ceiling) {
//////    while((k < ceiling) && m->getTile(j, i, k) == 0) k++;
//////    while((k < ceiling) && m->getTile(x, y, k) == 1) findWalls(x, y, k++);
//////    if (k < ceiling) {floors.insert({(double)x, (double)y, (double)k});}
//////  }
//////  return ground;
//////}
//////
//////void walkUp(int x, int y, int z, int ceiling) {
//////  y++;
//////  // if inside map
//////  int ground = findFloors(x, y, z, ceiling);
//////
//////  walkUp(x, y, ground, ceiling);
//////  walkUpRight(x, y, ground, ceiling);
//////  walkUpLeft(x, y, ground, ceiling);
//////}
////
/////*
////
////- Partir de la posicion del personaje (centro de la c�mara)
////- buscar suelo (si el personaje est� sobre el suelo, ese, si est� al aire, descender por niveles hasta encontrarlo).
////- Recorrer el mapa primero hacia atras (izq y arriba) y luego hacia adelante (der y abajo).
////- Por cada nueva casilla se busca el suelo a partir del suelo contiguo.
////  - Si al nivel actual la nueva casilla es aire, se desciende hasta encontrar el suelo.
////  - Si hay un bloque solido, se asciende hasta encontrar el nuevo nivel de suelo.
////
////*/
////
////void IsometricDrawer::draw() {
////  // - Partir de la posicion del personaje (centro de la c�mara)
////  // POR AHORA el centro del mapa
////  int x = m->getHW();
////  int y = m->getHH();
////  int z = m->getHD();
////
////  // buscar suelo (si el personaje est� sobre el suelo, ese, si est� al aire, descender por niveles hasta encontrarlo).
////  // POR AHORA siempre esta en el suelo
////
////  // - Recorrer el mapa primero hacia atras (izq y arriba) y luego hacia adelante (der y abajo).
////  // POR AHORA 0 es aire y 1 es tierra
////  int idx = x;
////  int idy = y;
////  int idz = z;
////  int k = idz;
////  // backward from center
////  for(int i = idy; i >= 0; i--) {
////    for(int j = idx; j >= 0; j--) {
////      //printf("x: %d, y: %d, d: %d\n", j, i, k); fflush(stdout);
////      // - Por cada nueva casilla se busca el suelo a partir del suelo contiguo.
////      //   - Si al nivel actual la nueva casilla es aire, se desciende hasta encontrar el suelo.
////      //   - Si hay un bloque solido, se asciende hasta encontrar el nuevo nivel de suelo.
////      while((k > 0) && m->getTile(j, i, k) == 0) k--;
////      while((k < (m->getD()-1)) && m->getTile(j, i, k) == 1) k++;
////      ground.insert({(double)j, (double)i, (double)k});
////      //  TODO insertar muros
////    }
////    idx = m->getW() - 1;
////  }
////
////  idx = x + 1;
////  k = idz;
////  // forward from center
////  for(int i = idy; i < m->getH(); i++) {
////    for(int j = idx; j < m->getW(); j++) {
////      //printf("x: %d, y: %d, d: %d\n", j, i, k); fflush(stdout);
////      // - Por cada nueva casilla se busca el suelo a partir del suelo contiguo.
////      //   - Si al nivel actual la nueva casilla es aire, se desciende hasta encontrar el suelo.
////      //   - Si hay un bloque solido, se asciende hasta encontrar el nuevo nivel de suelo.
////      while((k > 0) && m->getTile(j, i, k) == 0) k--;
////      while((k < (m->getD()-1)) && m->getTile(j, i, k) == 1) k++;
////      ground.insert({(double)j, (double)i, (double)k});
////      //  TODO insertar muros
////    }
////    idx = 0;
////  }
////
////  SDL_Rect src,dst;
////  for (auto &point : ground) {
////    //printf("x: %.1lf, y: %.1lf, d: %.1lf\n", point[0], point[1], point[2]); fflush(stdout);
////    const int iw = 16;
////    const int ih = 9;
////    const int ihw = iw / 2;
////    const int ihh = ih / 2;
////    src.x = 0;
////    src.y = 0;
////    src.w = 16;
////    src.h = 9;
////
////    int offset = ((int)(point[1]) % 2) ? ihw : 0;
////
////    dst.x = 100 + point[0] * iw + offset;
////    dst.y = 100 + point[1] * ihh - ih * point[2];
////    dst.w = 16;
////    dst.h = 9;
////    //printf("x: %d, y: %d\n", dst.x, dst.y); fflush(stdout);
////    window->render(grimage, &src, &dst);
////  }
////
////}
////
//int degryllmain(int, char**) {return 0;}
////  printf("--- Degryll main ---\n\n");
////
////  const int WIDTH = 1024;
////  const int HEIGHT = 768;
////
////  const char floorfilename[] = "data/images/degryll/isotetris/sueloT.png";
////  const char izqfilename[] = "data/images/degryll/isotetris/izqT.png";
////  const char derfilename[] = "data/images/degryll/isotetris/derT.png";
////
////  zbe::SDLWindow window(WIDTH,HEIGHT);
////  uint64_t floortile     = window.loadImg(floorfilename);
////  uint64_t izqtile       = window.loadImg(izqfilename);
////  uint64_t dertile       = window.loadImg(derfilename);
//////  window.loadImg(izqfilename);
//////  window.loadImg(derfilename);
////
////  const int mapW = 51;
////  const int mapH = 51;
////  const int mapD = 5;
////  int *map = new int[mapW * mapH * mapD];
////  for(int i = 0; i < mapH; i++) {
////    for(int j = 0; j < mapW; j++) {
////      for(int k = 0; k < mapD; k++) {
//////          if( k < 2) map[(i * mapW + j) * mapD + k] = 1;//(i < 50);
//////          else map[(i * mapW + j) * mapD + k] = 0;
////          map[(i * mapW + j) * mapD + k] = 1;
////      }
////    }
////  }
////  int value = 0;
////  for(int i = 0; i < mapH; i++) {
////    for(int j = 0; j < mapW; j++) {
////      if((i > 45) || (j > 45)) {
////        value = 0;
////      } else {
////        value = 1;
////      }
////      map[(i * mapW + j) * mapD + 4] = value;
////    }
////  }
////
////  for(int i = 0; i < mapH; i++) {
////    for(int j = 0; j < mapW; j++) {
////      if((i > 46) || (j > 46)) {
////        value = 0;
////      } else {
////        value = 1;
////      }
////      map[(i * mapW + j) * mapD + 3] = value;
////    }
////  }
////
////  for(int i = 0; i < mapH; i++) {
////    for(int j = 0; j < mapW; j++) {
////      if((i > 47) || (j > 47)) {
////        value = 0;
////      } else {
////        value = 1;
////      }
////      map[(i * mapW + j) * mapD + 2] = value;
////    }
////  }
////
////  for(int i = 0; i < mapH; i++) {
////    for(int j = 0; j < mapW; j++) {
////      if((i > 48) || (j > 48)) {
////        value = 0;
////      } else {
////        value = 1;
////      }
////      map[(i * mapW + j) * mapD + 1] = value;
////    }
////  }
////
////  for(int i = 0; i < mapH; i++) {
////    for(int j = 0; j < mapW; j++) {
////      if((i > 49) || (j > 49)) {
////        value = 0;
////      } else {
////        value = 1;
////      }
////      map[(i * mapW + j) * mapD + 0] = value;
////    }
////  }
//////  map[(50 * mapW + 50) * mapD + 0] = 1;
//////  map[(50 * mapW + 50) * mapD + 1] = 0;
//////  map[(50 * mapW + 50) * mapD + 2] = 0;
//////  map[(50 * mapW + 50) * mapD + 3] = 0;
//////  map[(50 * mapW + 50) * mapD + 4] = 0;
////
////  MultiLevelMap isomap(mapW, mapH, mapD, map);
////  IsometricDrawer isodrawer(&isomap, floortile, izqtile, dertile, &window);
////
////  bool keep = true;
////  while(keep){
////
////    window.clear();
////    isodrawer.draw();
////    window.present();
////
////    getchar();
////    getchar();
////    getchar();
////    getchar();
////    getchar();
////    getchar();
////  }
////
////  return (0);
////}
////
//////int degryllmain(int, char**) {
//////  printf("--- Degryll main ---\n\n");
//////
//////  srand(time(nullptr));
//////
//////    enum {
//////    INPUTEVENT = 0,
//////    COLLISIONEVENT = 1,
//////    TIMEEVENT = 2,
//////
//////    DRAWLIST = 1,
//////
//////    COLLISIONATORLIST = 1,
////////    MOBILELIST = 1,
////////    BALLACTUATORLIST = 1,
////////    COLLISIONABLELIST = 1,
////////    BOARDACTUATORLIST = 1,
////////    BRICKACTUATORLIST = 2,
//////
//////    WIDTH = 1024,
//////    HEIGHT = 768
//////  };
//////
//////  int *m;
//////  int w, h, l;
//////  loadMap("data/images/degryll/isotetris/mapa.txt", &m,  w, h, l);
//////  //printMap(m, w, h, l);
//////
//////  const char blockfilename[] = "data/images/batis/bloque_32.png";
//////  const char floorfilename[] = "data/images/degryll/isotetris/sueloT.png";
//////  const char izqfilename[] = "data/images/degryll/isotetris/izqT.png";
//////  const char derfilename[] = "data/images/degryll/isotetris/derT.png";
//////  const char charufilename[] = "data/images/degryll/isotetris/charUT.png";
//////  const char chardfilename[] = "data/images/degryll/isotetris/charDT.png";
//////  const char charlfilename[] = "data/images/degryll/isotetris/charLT.png";
//////  const char charrfilename[] = "data/images/degryll/isotetris/charRT.png";
//////  const char arcfilename[] = "data/images/degryll/isotetris/arcadeT.png";
//////  const char musicafilename[] = "data/images/degryll/isotetris/musica.png";
//////  const char murosfilename[] = "data/images/degryll/isotetris/muros.png";
//////  uint64_t blockgraphics;
//////  uint64_t floortile;
////////  uint64_t izqtile;
////////  uint64_t dertile;
////////  uint64_t charutile;
////////  uint64_t chardtile;
////////  uint64_t charltile;
////////  uint64_t charrtile;
////////  uint64_t arctile;
////////  uint64_t musicatile;
////////  uint64_t murostile;
//////
//////  zbe::EventStore& store = zbe::EventStore::getInstance();
//////
//////  zbe::SDLEventDispatcher & sdlEventDist = zbe::SDLEventDispatcher::getInstance();
//////  zbe::InputBuffer * inputBuffer = sdlEventDist.getInputBuffer();
//////  zbe::InputEventGenerator ieg(inputBuffer,INPUTEVENT);
//////
//////  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<GameReactor> >*> ctl;
//////  zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<GameReactor> >*> >& lmct = zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Interactionator<GameReactor> >*> >::getInstance();
//////  lmct.insert(COLLISIONATORLIST, &ctl);
//////  zbe::CollisionEventGenerator<GameReactor> ceg(COLLISIONATORLIST, COLLISIONEVENT);
//////
//////  zbe::TimeEventGenerator teg(TIMEEVENT);
//////
//////  zbe::Timer *sysTimer = new zbe::SDLTimer(true);
//////  zbe::SysTime &sysTime = zbe::SysTime::getInstance();
//////  sysTime.setSystemTimer(sysTimer);
//////
//////  zbe::Window window(WIDTH,HEIGHT);
//////  blockgraphics = window.loadImg(blockfilename);
//////  floortile     = window.loadImg(floorfilename);
////////  izqtile       = window.loadImg(izqfilename);
////////  dertile       = window.loadImg(derfilename);
////////  charutile     = window.loadImg(charufilename);
////////  chardtile     = window.loadImg(chardfilename);
////////  charltile     = window.loadImg(charlfilename);
////////  charrtile     = window.loadImg(charrfilename);
////////  arctile       = window.loadImg(arcfilename);
////////  musicatile    = window.loadImg(musicafilename);
////////  murostile     = window.loadImg(murosfilename);
//////  window.loadImg(izqfilename);
//////  window.loadImg(derfilename);
//////  window.loadImg(charufilename);
//////  window.loadImg(chardfilename);
//////  window.loadImg(charlfilename);
//////  window.loadImg(charrfilename);
//////  window.loadImg(arcfilename);
//////  window.loadImg(musicafilename);
//////  window.loadImg(murosfilename);
//////
////////  zbe::SimpleSpriteSDLDrawer drawer(&window);
//////  zbe::DaemonMaster drawMaster;
//////  zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite >*> sprites;
//////  zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite >*> >& lmdraw = zbe::RsrcStore< zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite >*> >::getInstance();
//////  lmdraw.insert(DRAWLIST, &sprites);
//////
//////  std::shared_ptr<zbe::Daemon> drawerDaemon(new  zbe::DrawerDaemon<zbe::SingleSprite, zbe::TicketedForwardList<zbe::AvatarEntity<zbe::SingleSprite >*> >(std::make_shared<zbe::SingleSpriteSDLDrawer>(&window), DRAWLIST));
//////  drawMaster.addDaemon(drawerDaemon);
//////
//////  zbe::TimedDaemonMaster behavMaster;
////////  std::vector<zbe::Mobile<2>*> vmobile;
////////  zbe::RsrcStore< std::vector<zbe::Mobile<2>*> >& lmmobile = zbe::RsrcStore< std::vector<zbe::Mobile<2>*> >::getInstance();
////////  lmmobile.insert(MOBILELIST, &vmobile);
////////  std::shared_ptr<zbe::Daemon> bball(new  zbe::BehaviorDaemon< zbe::Mobile<2>, std::vector<zbe::Mobile<2>*> >(new zbe::UniformLinearMotion<2>(), MOBILELIST));
////////  dMaster.addDaemon(bball);
//////
////////  zbe::Block block(0, 0, blockgraphics, DRAWLIST);
////////  block.setSimpleSpriteAdaptor(&blockAdaptor);
////////
////////  zbe::Block blockInv(0, 1, blockgraphics, DRAWLIST);
////////  blockInv.setSimpleSpriteAdaptor(&blockAdaptor);
//////
//////  zbetris::Board board(10, 20, blockgraphics, DRAWLIST);
//////
//////  zbetris::Tetromino tetromino(blockgraphics, DRAWLIST, board, 1);
////////  //ball
////////  std::forward_list< zbe::Actuator< zbe::MovableInteractioner<game::GameReactor, 2>, game::GameReactor >*> ballActuatorsList;
////////  zbe::RsrcStore< std::forward_list< zbe::Actuator< zbe::MovableInteractioner<game::GameReactor, 2>, game::GameReactor >* > >& lmBallActuatorsList = zbe::RsrcStore< std::forward_list< zbe::Actuator< zbe::MovableInteractioner<game::GameReactor, 2>, game::GameReactor >* > >::getInstance();
////////  lmBallActuatorsList.insert(BALLACTUATORLIST, &ballActuatorsList);
////////  game::GameBallBouncer gbBouncer;
////////  ballActuatorsList.push_front(&gbBouncer);
////////
////////  zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> collisionablesList;
////////  zbe::RsrcStore<zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> >& lmCollisionablesList = zbe::RsrcStore< zbe::TicketedForwardList<zbe::CollisionerEntity<game::GameReactor>*> >::getInstance();
////////  lmCollisionablesList.insert(COLLISIONABLELIST, &collisionablesList);
//////
//////
////////  zbe::SimpleSpriteAdaptor<zbe::Drawable>* spriteAdaptor = new zbe::SimpleDrawableSimpleSpriteAdaptor();
////////  zbe::BaseSphereMCMAPOAdaptor<game::GameReactor, 2> * movableCatorAdaptor = new zbe::BaseSphereMCMAPOAdaptor<game::GameReactor, 2>();
//////
//////  game::ExitInputHandler terminator;
//////  ieg.addHandler(zbe::ZBEK_ESCAPE, &terminator);
//////
//////  zbetris::MoveLeftInputHandler moveleft(tetromino);
//////  ieg.addHandler(zbe::ZBEK_a, &moveleft);
//////
//////  zbetris::MoveRightInputHandler moveright(tetromino);
//////  ieg.addHandler(zbe::ZBEK_d, &moveright);
//////
//////  zbetris::RotateLeftInputHandler rleft(tetromino);
//////  ieg.addHandler(zbe::ZBEK_SPACE, &rleft);
//////
//////  isolux::MiMap isomap(100, 100, w, h, l, m, 16, 9, floortile, DRAWLIST);
//////
//////  isolux::MoveCUInputHandler mud(isomap);
//////  ieg.addHandler(zbe::ZBEK_UP, &mud);
//////
//////  isolux::MoveCDInputHandler mcd(isomap);
//////  ieg.addHandler(zbe::ZBEK_DOWN, &mcd);
//////
//////  isolux::MoveCLInputHandler mld(isomap);
//////  ieg.addHandler(zbe::ZBEK_LEFT, &mld);
//////
//////  isolux::MoveCRInputHandler mrd(isomap);
//////  ieg.addHandler(zbe::ZBEK_RIGHT, &mrd);
//////
////////  for(int i = 0; i<1000 ; i++){
////////      //game::GameBall* ball = new game::GameBall(98.623993, 85.728439, 16 , -100, -100, BALLACTUATORLIST, COLLISIONABLELIST, ballgraphics);
////////      game::GameBall* ball = new game::GameBall((rand()%200 + 400), (rand()%200 + 400), 16 , (rand()%200 - 100), (rand()%200 - 100), BALLACTUATORLIST, COLLISIONABLELIST, ballgraphics);
////////      ctl.push_front(ball);
////////      ball->setSimpleSpriteAdaptor(spriteAdaptor);
////////      ball->setMovableCollisionatorAdaptor(movableCatorAdaptor);
////////      vmobile.push_back(ball);
////////      sprites.push_front(ball);
////////  }
//////
//////  //bricks
////////  zbe::RsrcStore< std::forward_list< zbe::Actuator<zbe::SimpleInteractioner<game::GameReactor>, game::GameReactor>*> >& lmSimpleConerActuatorsList = zbe::RsrcStore< std::forward_list< zbe::Actuator<zbe::SimpleInteractioner<game::GameReactor>, game::GameReactor>*> >::getInstance();
////////  std::forward_list< zbe::Actuator<zbe::SimpleInteractioner<game::GameReactor>, game::GameReactor>*> brickActuatorsList;
////////  lmSimpleConerActuatorsList.insert(BRICKACTUATORLIST, &brickActuatorsList);
////////  for(int i = 0; i<8 ; i++){
////////      for(int j = 0; j<8 ; j++){
////////          game::GameBlock *brick = new game::GameBlock(i*51+ 100, j*32 + 100, 51, 32, brickgraphics, BRICKACTUATORLIST);
////////          brick->setSimpleSpriteAdaptor(spriteAdaptor);
////////          collisionablesList.push_front(brick);
////////          sprites.push_front(brick);
////////      }
////////  }
//////
//////  //board
////////  std::forward_list< zbe::Actuator<zbe::SimpleInteractioner<game::GameReactor>, game::GameReactor>*> boardActuatorsList;
////////  lmSimpleConerActuatorsList.insert(BOARDACTUATORLIST, &boardActuatorsList);
////////  game::GameBoard board(WIDTH, HEIGHT, BOARDACTUATORLIST);
////////  collisionablesList.push_front(&board);
//////
//////  sysTimer->start();
//////  sdlEventDist.run();
//////  sysTime.update();
//////
//////  int64_t endT = sysTime.getTotalTime();// instant at which the frame ends
//////  int64_t initT = 0;//Lets start
//////
//////  int64_t maxFrameTime = zbe::SECOND / 64;
//////
//////  int tile = 0;
////////  int tilex = 0;
////////  int tiley = 0;
//////  int lasttile = 0;
//////
//////  bool keep = true;
//////  while(keep){
//////
//////    window.clear();
//////
//////    sdlEventDist.run();
//////    sysTime.update();
//////
//////    initT = endT;
//////    endT = sysTime.getTotalTime();
//////
//////    if((endT - maxFrameTime)>initT){
//////      initT = endT - maxFrameTime;
//////    }
//////
////////    int pos = (endT/zbe::SECOND)%10;
////////    if(pos % 2) {
////////      blockInv.setInvisible();
////////    } else {
////////      blockInv.setVisible();
////////    }
////////
////////    block.setX(pos);
//////
//////    //board.setTile(tilex, tiley, 0);
//////
//////    tile = (endT/(zbe::SECOND/4))%240;
////////    tilex = tile % 10;
////////    tiley = tile / 10;
//////
//////   // board.setTile(tilex, tiley, 1);
//////    if ((lasttile != tile) && board.getLines() <= 9) {
//////      lasttile = tile;
//////      tetromino.drop();
//////    }
//////    if ((board.getLines() > 9) && (board.getLines() < 30)){
//////      isomap.activate();
//////      board.setLines(99);
//////    }
//////    //tetromino.setType((tile / 4) % 8, tile % 4);
//////
//////    //printf("Tile: %d (%d, %d)\n", tile, tilex, tiley);
//////    while (initT < endT) {
//////
//////      ieg.generate(initT,endT);
//////      teg.generate(initT,endT);
//////      ceg.generate(initT,endT);
//////
//////      int64_t eventTime = store.getTime();
//////      if (eventTime <= endT) {  zbe::TimedDaemonMaster behavMaster;
//////        behavMaster.run(eventTime-initT);
//////        store.manageCurrent();
//////        initT = eventTime;
//////      } else {
//////        behavMaster.run(endT-initT);
//////        store.clearStore();
//////        initT = endT;
//////      }
//////    }
//////
//////    drawMaster.run();
////////    for(auto s : sprites){
////////        drawer.apply(s->getSimpleSprite().get());
////////    }
//////
//////    /* If one or more error occurs, the ammount and the first one
//////     * will be stored into SysError structure, so it can be consulted.
//////     *
//////     * If there are errors, the first one will be prompted.
//////     */
//////    int errcount = zbe::SysError::getNErrors();
//////    if(errcount>0){
//////        printf("Error: %s",zbe::SysError::getFirstErrorString().c_str());fflush(stdout);
//////    }
//////    window.present();
//////  }
//////
//////  return (0);
//////}
