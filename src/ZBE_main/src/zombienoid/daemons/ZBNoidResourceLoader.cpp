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

  void ZBNoidResourceLoader::run () {
     idStore->setId(ZBNCfg::BOARD_GRAPHICS, store->loadImg(backImg));

     idStore->setId(ZBNCfg::ITEM_LIFE_GRAPHICS, store->loadImg(extraLife));
     idStore->setId(ZBNCfg::ITEM_MULTIPLIER_GRAPHICS, store->loadImg(multiplier));
     idStore->setId(ZBNCfg::ITEM_ACCEL_GRAPHICS, store->loadImg(accelerator));
     idStore->setId(ZBNCfg::ITEM_DECEL_GRAPHICS, store->loadImg(decelerator));
     idStore->setId(ZBNCfg::ITEM_BIGGER_GRAPHICS, store->loadImg(bigger));
     idStore->setId(ZBNCfg::ITEM_SMALLER_GRAPHICS, store->loadImg(smaller));
     idStore->setId(ZBNCfg::ITEM_MAGNET_GRAPHICS, store->loadImg(magnet));
     idStore->setId(ZBNCfg::ITEM_P100_GRAPHICS, store->loadImg(points100));
     idStore->setId(ZBNCfg::ITEM_P200_GRAPHICS, store->loadImg(points200));
     idStore->setId(ZBNCfg::ITEM_P500_GRAPHICS, store->loadImg(points500));
     idStore->setId(ZBNCfg::ITEM_P999_GRAPHICS, store->loadImg(points999));
     idStore->setId(ZBNCfg::ITEM_PN5000_GRAPHICS, store->loadImg(pointsn5000));

    idStore->setId(ZBNCfg::BRICK_GRAHPICS, store->loadImg(brickImg));

    idStore->setId(ZBNCfg::BAR_GRAPHICS, store->loadImg(barImg));
    idStore->setId(ZBNCfg::BAR_GRAPHICS_GREY, store->loadImg(barImgGrey));

    idStore->setId(ZBNCfg::BALL_N_GRAPHICS, store->loadImg(ballImgNormal));
    idStore->setId(ZBNCfg::BALL_B_GRAPHICS, store->loadImg(ballImgBoomb));
    idStore->setId(ZBNCfg::EXPLODE_GRAPHICS, store->loadImg(explosion));
  }

}
