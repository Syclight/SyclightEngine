#pragma once

#include <fmod.hpp> // FMOD 头文件
#include <iostream>
#include <string>

class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();

    // 加载并播放背景音乐
    bool playBackgroundMusic(const std::string& filePath);
    // 更新 FMOD 系统（每帧调用）
    void update();
	// 停止当前播放的音频
    void stopAudio();
	// 暂停当前播放的音频
    void pauseAudio();
	// 恢复当前播放的音频
    void resumeAudio();
	// 设置音量
	void setVolume(float volume);
	// 获取当前音量
	float getVolume() const;
	// 获取当前音频的播放位置（秒）
	float getCurrentPosition() const;
	// 设置音频的播放位置（毫秒）
	void setCurrentPosition(float position);
	// 获取音频的持续时间（秒）
	float getDuration() const;

private:
    FMOD::System* system = nullptr;
    FMOD::Sound* sound = nullptr;
    FMOD::Channel* channel = nullptr;
};

