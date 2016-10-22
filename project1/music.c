#include "miner.h"

void lose_music()
{
    WAVE *pwave;

    initsound(); // 初始化声卡
    pwave = load_wave("Bomb.wav"); // 载入wav文件, 返回WAVE指针
    play_wave(pwave, 1);  // repeat 1 times 播放wav声音
    getchar();
    free_wave(pwave); // 释放wav声音占用的资源
    closesound(); // 关闭声卡
} 

void end_music()
{
    MIDI *pmidi;

    initsound(); // 初始化声卡
    pmidi = load_midi("dream.mid");  // 载入midi文件, 返回MIDI指针

    play_midi(pmidi, -1); // repeat forever 播放midi音乐

    getchar();

    free_midi(pmidi); // 释放midi音乐占用的资源
    closesound(); // 关闭声卡
}

