// /**
//  * Copyright 2012 Batis Degryll Ludo
//  * @file Ftry.h
//  * @since 2018-11-07
//  * @date 2018-11-21
//  * @author Ludo Degryll Batis
//  * @brief Generic Factory.
//  */
//
// #ifndef ZBE_FACTORIES_IMPLEMENTATIONS_ENTITIES_AVATARS_SIMPLEANIMSPRTFTRY_H_
// #define ZBE_FACTORIES_IMPLEMENTATIONS_ENTITIES_AVATARS_SIMPLEANIMSPRTFTRY_H_
//
// #include <string>
// #include <nlohmann/json.hpp>
//
// #include "ZBE/core/entities/AvatarEntity.h"
//
// #include "ZBE/core/tools/containers/RsrcStore.h"
//
// #include "ZBE/factories/Factory.h"
//
// #include "ZBE/core/system/system.h"
//
// #include "ZBE/core/entities/avatars/implementations/SimpleAnimatedSprite.h"
//
// namespace zbe {
//
// /** \brief Generic Factory.
//  */
// template<typename List, const char *listnamespace>
// class SimpleAnimSprtFtry : virtual public Factory {
// public:
//   /** \brief Creates an item from a file.
//    *  \param name Name for the created item.
//    *  \param cfgId item's configuration id.
//    */
//   void create(std::string name, uint64_t) override;
//
//   /** \brief Set-up an item.
//    *  \param name Name for the created item.
//    *  \param cfgId item's configuration id.
//    */
//   void setup(std::string, uint64_t);
// private:
//   RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
//   RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
//   RsrcDictionary<double>& doubleStore = RsrcDictionary<double>::getInstance();
//   RsrcStore<List>& listStore = RsrcStore<List>::getInstance();
//   //RsrcStore<AvatarEntityFixed<AnimatedSprite> >& aefSasStore = RsrcStore<AvatarEntityFixed<AnimatedSprite> >::getInstance();
//   RsrcStore<SimpleAnimatedSprite*>& sasPtrRsrc = RsrcStore<SimpleAnimatedSprite*>::getInstance();
//   RsrcStore<Ticket>& ticketStore = RsrcStore<Ticket>::getInstance();
//   RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
//   RsrcStore<ContextTime> &timeRsrc = RsrcStore<ContextTime>::getInstance();
// };
//
// template<typename List, const char *listnamespace>
// void SimpleAnimSprtFtry<List, listnamespace>::create(std::string name, uint64_t cfgId) {
//   using namespace std::string_literals;
//   using namespace nlohmann;
//   auto sas = new SimpleAnimatedSprite();
//   auto aef = std::make_shared<AvatarEntityFixed<AnimatedSprite> >(sas);
//   sasPtrRsrc.insert("SimpleAnimatedSpritePtr."s + name, std::make_shared<SimpleAnimatedSprite*>(sas));
//   std::shared_ptr<json> cfg = configRsrc.get(cfgId);
//   if(cfg) {
//     auto j = *cfg;
//     if (!j["lists"].is_array()) {
//       SysError::setError("SimpleAnimatedSprite config for list must be a string."s);
//       return;
//     }
//     auto lists = j["lists"];
//     auto aec = std::make_shared<AvatarEntityContainer<AnimatedSprite> >(aef);
//     for (auto& e : lists.items()) {
//       auto lConfig = e.value();
//       if (!lConfig.is_string()) {
//         SysError::setError("SimpleAnimatedSprite lists contains invalid data."s);
//         return;
//       }
//       std::string listname = lConfig.get<std::string>();
//       auto list = listStore.get(std::string(listnamespace)+"."+listname);
//       auto ticket = list->push_front(aec);
//       ticketStore.insert("Ticket."s + name, ticket);
//     }
//   } else {
//     SysError::setError("SimpleAnimatedSprite config for "s + name + " not found."s);
//   }
// }
//
// template<typename List, const char *listnamespace>
// void SimpleAnimSprtFtry<List, listnamespace>::setup(std::string name, uint64_t cfgId) {
//   using namespace std::string_literals;
//   using namespace nlohmann;
//   std::shared_ptr<json> cfg = configRsrc.get(cfgId);
//   if(cfg) {
//     auto j = *cfg;
//     if (!j["contexttime"].is_string()) {
//       SysError::setError("SimpleAnimatedSprite config for contexttime must be a string."s);
//       return;
//     }
//     if (!j["time"].is_string()) {
//       SysError::setError("SimpleAnimatedSprite config for time must be a string."s);
//       return;
//     }
//     if (!j["state"].is_string()) {
//       SysError::setError("SimpleAnimatedSprite config for state must be a string."s);
//       return;
//     }
//     if (!j["degrees"].is_string()) {
//       SysError::setError("SimpleAnimatedSprite config for degrees must be a string."s);
//       return;
//     }
//     if (!j["x"].is_string()) {
//       SysError::setError("SimpleAnimatedSprite config for x must be a string."s);
//       return;
//     }
//     if (!j["y"].is_string()) {
//       SysError::setError("SimpleAnimatedSprite config for y must be a string."s);
//       return;
//     }
//     if (!j["w"].is_string()) {
//       SysError::setError("SimpleAnimatedSprite config for w must be a string."s);
//       return;
//     }
//     if (!j["h"].is_string()) {
//       SysError::setError("SimpleAnimatedSprite config for h must be a string."s);
//       return;
//     }
//     if (!j["graphics"].is_string()) {
//       SysError::setError("SimpleAnimatedSprite config for graphics must be a string."s);
//       return;
//     }
//
//     std::string contexttimename = j["contexttime"].get<std::string>();
//     std::string timename = j["time"].get<std::string>();
//     std::string statename = j["state"].get<std::string>();
//     std::string degreesname = j["degrees"].get<std::string>();
//     std::string xname = j["x"].get<std::string>();
//     std::string yname = j["y"].get<std::string>();
//     std::string wname = j["w"].get<std::string>();
//     std::string hname = j["h"].get<std::string>();
//     std::string graphicsname = j["graphics"].get<std::string>();
//
//     std::shared_ptr<ContextTime> cTime = timeRsrc.get("ContextTime."s + contexttimename);
//     uint64_t time  = (uint64_t)intStore.get(timename);
//     int64_t state  = intStore.get(statename);
//     double degrees = doubleStore.get(degreesname);
//     int64_t x = intStore.get(xname);
//     int64_t y = intStore.get(yname);
//     int64_t w = intStore.get(wname);
//     int64_t h = intStore.get(hname);
//     uint64_t graphics = uintStore.get(graphicsname);
//
//     SimpleAnimatedSprite* sas = *(sasPtrRsrc.remove("SimpleAnimatedSpritePtr."s + name));
//
//     sas->setContextTime(cTime);
//     sas->setTime(time);
//     sas->setState(state);
//     sas->setDegrees(degrees);
//     sas->setX(x);
//     sas->setY(y);
//     sas->setW(w);
//     sas->setH(h);
//     sas->setGraphics(graphics);
//   } else {
//     SysError::setError("SimpleAnimatedSprite config for "s + name + " not found."s);
//   }
// }
//
// } // namespace ZBE
//
// #endif // ZBE_FACTORIES_IMPLEMENTATIONS_ENTITIES_AVATARS_SIMPLEANIMSPRTFTRY_H_
