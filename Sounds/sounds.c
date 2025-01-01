#include "sounds.h"

static SDL_AudioDeviceID _audioDeviceId = 0;
static Uint8 *_audioBuffer = NULL;
static Uint32 _audioLength = 0;

void play_sound()
{
    int errorCode = SDL_OK;

    errorCode = initialize_audio();
    if (errorCode)
    {
        return;
    }
    play_audio();
}

int initialize_audio()
{
    SDL_AudioSpec audioSpec;
    SDL_memset(&audioSpec, 0, sizeof(audioSpec));
    SDL_AudioSpec obtained;
    SDL_memset(&obtained, 0, sizeof(obtained));

    audioSpec.callback = audio_callback;
    audioSpec.channels = 2;
    audioSpec.freq = 44100;
    audioSpec.format = AUDIO_S16;
    audioSpec.samples = 2048;

    _audioDeviceId = SDL_OpenAudioDevice(NULL, 0, &audioSpec, &obtained, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    if (_audioDeviceId == INVALID_AUDIO_DEVICE)
    {
        return -2; /* Could not open Device */
    }

    if (SDL_LoadWAV("../Assets/Sounds/music.wav", &audioSpec, &_audioBuffer, &_audioLength) == NULL)
    {
        return -3; /* File Not Found */
    }

    return SDL_OK;
}

void audio_callback(void *userData, Uint8 *stream, int length)
{
    if (_audioLength == 0)
    {
        initialize_audio();
    }
    if (length > (int)_audioLength)
    {
        length = _audioLength;
    }

    memset(stream, 0, length); /* Silence everything */
    SDL_MixAudioFormat(stream, _audioBuffer, AUDIO_S16, length, 25);

    _audioBuffer += length;
    _audioLength -= length;
}

void play_audio()
{
    SDL_PauseAudioDevice(_audioDeviceId, PLAY_AUDIO);
}

void stop_audio()
{
    SDL_PauseAudioDevice(_audioDeviceId, STOP_AUDIO);
    clean_up();
}
void clean_up()
{
    SDL_CloseAudioDevice(_audioDeviceId);
}