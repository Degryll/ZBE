/**
 * Copyright 2025 Batis Degryll Ludo
 * @file SysTime.h
 * @since 2025-05-12
 * @date 2025-05-12
 * @author Ludo Degryll Batis
 * @brief Tool used to ask about system time.
 */

 #include "ZBE/core/system/SysTime.h"

 namespace zbe {
 
 #ifdef _WIN32
 
 template class ZBEAPI std::shared_ptr<Timer>;
 
 #endif // OS
 
 }  // namespace zbe
 