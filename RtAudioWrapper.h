#ifndef __RTAUDIOWRAPER_H__
#define __RTAUDIOWRAPER_H__

#include "RtAudio.h"

#include <iostream>
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <assert.h>

const unsigned int AUDIOBUFFERLEN = 512;
struct AudioData
{
	short data[AUDIOBUFFERLEN];
	double stream_time;
};

class RtAudioWrapper
{
public:
	RtAudioWrapper();
	RtAudioWrapper(int device_id, int num_channel, int sample_rate);
	~RtAudioWrapper();

	bool open(const int divice_id);
	void list_devices();
	bool grab();
	bool retrieve(AudioData &audio_data);
	void init();

private:
	RtAudioWrapper(const RtAudioWrapper&) {};
	RtAudioWrapper& operator=(const RtAudioWrapper&) {};

	std::shared_ptr<RtAudio> rtaudio_;

	// audio data stuff
	std::deque<AudioData> v_audiodata_;
	AudioData audio_data_;
	std::mutex mutex_;
	std::condition_variable condition_variable_;
	bool cond_notify_;

	// audio information stuff
	int device_id_;
	int num_channels_;
	int sample_rate_;
	unsigned int buffer_frames_; 
	bool is_grabed_;
};

#endif // !__RTAUDIOWRAPER_H__