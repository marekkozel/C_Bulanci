#include "sounds.h"

/* VARIABLES */
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
    clean_up();
}

static int initialize_audio()
{
    SDL_AudioSpec audioSpec;
    SDL_AudioSpec obtained;

    audioSpec.channels = CHANNELS;
    audioSpec.freq = SAMPLE_RATE;
    audioSpec.format = SDL_AUDIO_FORMAT;
    audioSpec.callback = audio_callback;

    _audioDeviceId = SDL_OpenAudioDevice(NULL, 0, &audioSpec, &obtained, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
    if (_audioDeviceId == INVALID_AUDIO_DEVICE)
    {
        return -2; /* Could not open Device */
    }

    if (SDL_LoadWAV("../Assets/Sounds/get_hited.wav", &audioSpec, &_audioBuffer, &_audioLength) == NULL)
    {
        return -3; /* File Not Found */
    }

    return SDL_OK;
}

static void audio_callback(void *userData, Uint8 *stream, int length)
{
    if (_audioLength == 0)
    {
        return;
    }
    if (length > (int)_audioLength)
    {
        length = _audioLength;
    }

    memset(stream, 0, length); /* Silence everything */
    SDL_MixAudioFormat(stream, _audioBuffer, SDL_AUDIO_FORMAT, length, SDL_MIX_MAXVOLUME);

    _audioBuffer += length;
    _audioLength -= length;
}

static void play_audio()
{
    SDL_PauseAudioDevice(_audioDeviceId, PLAY_AUDIO);
    SDL_Delay(AUDIO_LENGTH_MS);
    SDL_PauseAudioDevice(_audioDeviceId, STOP_AUDIO);
}
static void clean_up()
{
    SDL_CloseAudioDevice(_audioDeviceId);
    // SDL_FreeWAV(_audioBuffer);
}