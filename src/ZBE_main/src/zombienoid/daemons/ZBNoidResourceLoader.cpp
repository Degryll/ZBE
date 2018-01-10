#include "zombienoid/daemons/ZBNoidResourceLoader.h"

namespace zombienoid{

  //Bricks
  const char brickImg[] = "data/images/zombieball/braikn_64.png";
  // Balls
  const char ballImgNormal[] = "data/images/zombieball/zball_n.png";
  const char ballImgBoomb[] = "data/images/zombieball/zball_b.png";
  //bars
  const char barImg[] = "data/images/zombieball/zombar_color_32.png";
  const char barImgGrey[] = "data/images/zombieball/zombar_grey_32.png";
  //Items
  const char extraLife[] = "data/images/zombieball/zbeza_life_32.png";
  const char multiplier[] = "data/images/zombieball/zbeza_tbal_32.png";
  const char accelerator[] = "data/images/zombieball/zbeza_acel_32.png";
  const char decelerator[] = "data/images/zombieball/zbeza_dcel_32.png";
  const char bigger[] = "data/images/zombieball/zbeza_ebal_32.png";
  const char smaller[] = "data/images/zombieball/zbeza_rbal_32.png";
  const char magnet[] = "data/images/zombieball/zbeza_sbar_32.png";
  const char points100[] = "data/images/zombieball/zbeza_pnts_100_32.png";
  const char points200[] = "data/images/zombieball/zbeza_pnts_200_32.png";
  const char points500[] = "data/images/zombieball/zbeza_pnts_500_32.png";
  const char points999[] = "data/images/zombieball/zbeza_pnts_999_32.png";
  const char pointsn5000[] = "data/images/zombieball/zbeza_pntn_32.png";
  //Explosion
  const char explosion[] = "data/images/zombieball/boom_002_256.png";
  //Back
  const char backImg[]   = "data/images/zombieball/bck.png";
  //Fonts
  const char fontFileName[] = "data/fonts/PublicEnemyNF.ttf";
  //Font colors
  const SDL_Color boomTextColor{255, 255, 0, 192};
  const SDL_Color textColor{255, 128, 0, 255};

  void ZBNoidResourceLoader::run () {

     srand(time(0));
     
     rsrcIDDic->setId(ZBNCfg::BOARD_GRAPHICS, imgStore->loadImg(backImg));

     rsrcIDDic->setId(ZBNCfg::ITEM_LIFE_GRAPHICS, imgStore->loadImg(extraLife));
     rsrcIDDic->setId(ZBNCfg::ITEM_MULTIPLIER_GRAPHICS, imgStore->loadImg(multiplier));
     rsrcIDDic->setId(ZBNCfg::ITEM_ACCEL_GRAPHICS, imgStore->loadImg(accelerator));
     rsrcIDDic->setId(ZBNCfg::ITEM_DECEL_GRAPHICS, imgStore->loadImg(decelerator));
     rsrcIDDic->setId(ZBNCfg::ITEM_BIGGER_GRAPHICS, imgStore->loadImg(bigger));
     rsrcIDDic->setId(ZBNCfg::ITEM_SMALLER_GRAPHICS, imgStore->loadImg(smaller));
     rsrcIDDic->setId(ZBNCfg::ITEM_MAGNET_GRAPHICS, imgStore->loadImg(magnet));
     rsrcIDDic->setId(ZBNCfg::ITEM_P100_GRAPHICS, imgStore->loadImg(points100));
     rsrcIDDic->setId(ZBNCfg::ITEM_P200_GRAPHICS, imgStore->loadImg(points200));
     rsrcIDDic->setId(ZBNCfg::ITEM_P500_GRAPHICS, imgStore->loadImg(points500));
     rsrcIDDic->setId(ZBNCfg::ITEM_P999_GRAPHICS, imgStore->loadImg(points999));
     rsrcIDDic->setId(ZBNCfg::ITEM_PN5000_GRAPHICS, imgStore->loadImg(pointsn5000));

    rsrcIDDic->setId(ZBNCfg::BRICK_GRAHPICS, imgStore->loadImg(brickImg));

    rsrcIDDic->setId(ZBNCfg::BAR_GRAPHICS, imgStore->loadImg(barImg));
    rsrcIDDic->setId(ZBNCfg::BAR_GRAPHICS_GREY, imgStore->loadImg(barImgGrey));

    rsrcIDDic->setId(ZBNCfg::BALL_N_GRAPHICS, imgStore->loadImg(ballImgNormal));
    rsrcIDDic->setId(ZBNCfg::BALL_B_GRAPHICS, imgStore->loadImg(ballImgBoomb));
    rsrcIDDic->setId(ZBNCfg::EXPLODE_GRAPHICS, imgStore->loadImg(explosion));

    rsrcIDDic->setId(ZBNCfg::BOOM_TEXT_FONT, textFontStore->loadFont(fontFileName, TEXT_B_SIZE, boomTextColor));
    rsrcIDDic->setId(ZBNCfg::TEXT_FONT, textFontStore->loadFont(fontFileName, TEXT_F_SIZE, textColor));

    zbe::ResourceManager<zbe::SpriteSheet<zbe::AnimatedSprite> >& rmss = zbe::ResourceManager<zbe::SpriteSheet<zbe::AnimatedSprite> >::getInstance();

    ImgSrcDef boardGraphics;
    boardGraphics.frameAmount = BOARD_FRAMES;
    boardGraphics.frameDisplacemet = BOARD_DISPLACEMENT;
    boardGraphics.frameTime = BOARD_FRAMETIME;
    boardGraphics.intialRegion = BOARD_REGION;
    boardGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::BOARD_GRAPHICS);

    MultiSpriteSheet* boardSheet = new MultiSpriteSheet(BOARD_STATES, boardGraphics);

    std::shared_ptr<zbe::SpriteSheet<zbe::AnimatedSprite> > boardSS(boardSheet);
    rmss.insert(ZBNCfg::BOARD_SS, boardSS);

    ImgSrcDef itemGraphics;
    itemGraphics.frameAmount = ITEM_FRAMES;
    itemGraphics.frameDisplacemet = ITEM_DISPLACEMENT;
    itemGraphics.frameTime = ITEM_FRAMETIME;
    itemGraphics.intialRegion = ITEM_REGION;
    itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_LIFE_GRAPHICS);

    MultiSpriteSheet* itemSheet = new MultiSpriteSheet(ITEM_TYPES, itemGraphics);
    itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_MULTIPLIER_GRAPHICS);
    itemSheet->setImgSrcDef(1, itemGraphics);
    itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_ACCEL_GRAPHICS);
    itemSheet->setImgSrcDef(2, itemGraphics);
    itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_DECEL_GRAPHICS);
    itemSheet->setImgSrcDef(3, itemGraphics);
    itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_BIGGER_GRAPHICS);
    itemSheet->setImgSrcDef(4, itemGraphics);
    itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_SMALLER_GRAPHICS);
    itemSheet->setImgSrcDef(5, itemGraphics);
    itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_MAGNET_GRAPHICS);
    itemSheet->setImgSrcDef(6, itemGraphics);
    itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_P100_GRAPHICS);
    itemSheet->setImgSrcDef(7, itemGraphics);
    itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_P200_GRAPHICS);
    itemSheet->setImgSrcDef(8, itemGraphics);
    itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_P500_GRAPHICS);
    itemSheet->setImgSrcDef(9, itemGraphics);
    itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_P999_GRAPHICS);
    itemSheet->setImgSrcDef(10, itemGraphics);
    itemGraphics.imgSrcId = rsrcIDDic->getId(ZBNCfg::ITEM_PN5000_GRAPHICS);
    itemSheet->setImgSrcDef(11, itemGraphics);

    std::shared_ptr<zbe::SpriteSheet<zbe::AnimatedSprite> > itemSS(itemSheet);
    rmss.insert(ZBNCfg::ITEM_SS, itemSS);

    ImgSrcDef barGrapDef;
    barGrapDef.frameAmount = BAR_FRAMES;
    barGrapDef.frameDisplacemet = BAR_DISPLACEMENT;
    barGrapDef.frameTime = BAR_FRAMETIME;
    barGrapDef.intialRegion = BAR_REGION;
    barGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::BAR_GRAPHICS);

    MultiSpriteSheet* barSheet = new MultiSpriteSheet(2, barGrapDef);
    barGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::BAR_GRAPHICS_GREY);
    barSheet->setImgSrcDef(1,barGrapDef);

    std::shared_ptr<zbe::SpriteSheet<zbe::AnimatedSprite> > barSS(barSheet);
    rmss.insert(ZBNCfg::BAR_SS, barSS);

    ImgSrcDef ballGrapDef;
    ballGrapDef.frameAmount = BALL_FRAMES;
    ballGrapDef.frameDisplacemet = BALL_DISPLACEMENT;
    ballGrapDef.frameTime = BALL_FRAMETIME;
    ballGrapDef.intialRegion = BALL_REGION;
    ballGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::BALL_N_GRAPHICS);

    MultiSpriteSheet* ballSheet = new MultiSpriteSheet(2, ballGrapDef);
    ballGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::BALL_B_GRAPHICS);
    ballSheet->setImgSrcDef(BALL_BOOM_STATE,ballGrapDef);

    std::shared_ptr<zbe::SpriteSheet<zbe::AnimatedSprite> > ballSS(ballSheet);
    rmss.insert(ZBNCfg::BALL_SS, ballSS);

    ImgSrcDef explosionGrapDef;
    explosionGrapDef.frameAmount = EXPLOSION_FRAMES;
    explosionGrapDef.frameDisplacemet = EXPLOSION_DISPLACEMENT;
    explosionGrapDef.frameTime = EXPLOSION_FRAMETIME;
    explosionGrapDef.intialRegion = EXPLOSION_REGION;
    explosionGrapDef.imgSrcId = rsrcIDDic->getId(ZBNCfg::EXPLODE_GRAPHICS);

    MultiSpriteSheet* explosionSheet = new MultiSpriteSheet(1, explosionGrapDef);

    std::shared_ptr<zbe::SpriteSheet<zbe::AnimatedSprite> > explosionSS(explosionSheet);
    rmss.insert(ZBNCfg::EXPLSION_SS, explosionSS);

  }

}
