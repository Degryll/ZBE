///**
//* Copyright 2015 Batis Degryll Ludo
//* @file RsrcFolderLoader.cpp
//* @since 2018-07-07
//* @date 2018-07-07
//* @author Batis Degryll Ludo
//* @brief class ZBEAPI that loads all compatible resources within a folder.
//*/
//
//#include "ZBE/resources/loaders/RsrcFolderLoader.h"
//
//namespace zbe {
//
//void RsrcFolderLoader::load(std::string folder) {
//namespace fs = std::filesystem;
//for(auto& p : fs::directory_iterator(folder)) {
//  if(rsrcLoader->isLoadable(p.path().extension())){
//    rsrcLoader->load(p);
//  }
//}  // for auto& p
//}
//
//}  // namespace zbe
