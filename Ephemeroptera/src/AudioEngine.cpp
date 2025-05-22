#include "AudioEngine.h"

AudioEngine::AudioEngine()
{
    // 初始化 FMOD 系统
    FMOD::System_Create(&system);
    system->init(32, FMOD_INIT_NORMAL, nullptr); // 32 个通道，普通初始化
}

AudioEngine::~AudioEngine()
{
    // 清理资源
    if (sound) sound->release();
    if (system) system->release();
}

bool AudioEngine::playBackgroundMusic(const std::string& filePath)
{
    // 创建音频流
    FMOD_RESULT result = system->createStream(filePath.c_str(), FMOD_LOOP_NORMAL | FMOD_2D, nullptr, &sound);
    if (result != FMOD_OK) {
        std::cerr << "Failed to load sound: " << filePath << std::endl;
        return false;
    }

    // 播放音频
    result = system->playSound(sound, nullptr, false, &channel);
    if (result != FMOD_OK) {
        std::cerr << "Failed to play sound: " << filePath << std::endl;
        return false;
    }

    // 设置音量（0.0f 到 1.0f）
    channel->setVolume(0.5f);
    return true;
}

void AudioEngine::update()
{
    if (system) system->update();
}

void AudioEngine::stopAudio()
{
    if (channel) {
        channel->stop();
        channel = nullptr;
    }
}

void AudioEngine::pauseAudio()
{
    if (channel) {
        channel->setPaused(true);
    }
}

void AudioEngine::resumeAudio()
{
    if (channel) {
        channel->setPaused(false);
    }
}

void AudioEngine::setVolume(float volume)
{
    if (channel) {
        channel->setVolume(volume);
    }
}

float AudioEngine::getVolume() const
{
    float volume = 0.0f;
    if (channel) {
        channel->getVolume(&volume);
    }
    return volume;
}

float AudioEngine::getCurrentPosition() const
{
    unsigned int position = 0;
    if (channel) {
        channel->getPosition(&position, FMOD_TIMEUNIT_MS);
    }
    return static_cast<float>(position) / 1000.0f; // 转换为秒
}

void AudioEngine::setCurrentPosition(float position)
{
    if (channel) {
        unsigned int pos = static_cast<unsigned int>(position * 1000.0f); // 转换为毫秒
        channel->setPosition(pos, FMOD_TIMEUNIT_MS);
    }
}

float AudioEngine::getDuration() const
{
    unsigned int duration = 0;
    if (sound) {
        sound->getLength(&duration, FMOD_TIMEUNIT_MS);
    }
    return static_cast<float>(duration) / 1000.0f; // 转换为秒
}
