#include "miner.h"

void lose_music()
{
    WAVE *pwave;

    initsound(); // ��ʼ������
    pwave = load_wave("Bomb.wav"); // ����wav�ļ�, ����WAVEָ��
    play_wave(pwave, 1);  // repeat 1 times ����wav����
    getchar();
    free_wave(pwave); // �ͷ�wav����ռ�õ���Դ
    closesound(); // �ر�����
} 

void end_music()
{
    MIDI *pmidi;

    initsound(); // ��ʼ������
    pmidi = load_midi("dream.mid");  // ����midi�ļ�, ����MIDIָ��

    play_midi(pmidi, -1); // repeat forever ����midi����

    getchar();

    free_midi(pmidi); // �ͷ�midi����ռ�õ���Դ
    closesound(); // �ر�����
}

