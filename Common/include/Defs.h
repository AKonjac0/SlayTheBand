#ifndef DEFS_H
#define DEFS_H

#define PLAYER_MAX_HP 100
#define ENEMY_MAX_HP 30
#define PLAYER_MAX_MP 3

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

// 从左下角开始，第一象限中的 x,y，尽量保证 y 是一样的，这样血条高度一致（利用 Player 的位置计算 Enemy 的位置，保持对称）
#define PLAYER_POSITION_X 200
#define PLAYER_POSITION_Y 280

// 位置可以固定，图像大小由贴图大小决定，就不宏定义了

#define LOG qDebug() << __FILE__ << ":" << __LINE__ << ":"

#endif // DEFS_H
