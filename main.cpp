#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <iostream>
int main(int argc, char *argv[]) {
    ALuint source;
    ALCdevice *device;
    ALCcontext *context;

    device = alcOpenDevice(NULL);
    if (device == NULL)
    {
        //ALenum error = alcGetError();
        std::cout<< "error is errory";
        /* do something with the error */
        return -1;
    }
    /* Omit error checking */
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    /* Do more things */
    alGenSources(1, &source);
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1);
    alSource3f(source, AL_POSITION, 10, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, 1);


    //new
    char*     alBuffer;             //data for the buffer
    ALenum alFormatBuffer;    //buffer format
    ALsizei   alFreqBuffer;       //frequency
    ALsizei       alBufferLen;        //bit depth
    ALboolean    alLoop;         //loop


    //load the wave file //new
    //http://www.gamedev.net/topic/394781-alutloadwavfile/
    alutLoadWAVFile((ALbyte *)"my_music.wav",&alFormatBuffer,
                    (void **) &alBuffer,
                    &alBufferLen, &alFreqBuffer, &alLoop);


    ALsizei size, freq;
    ALenum format;
    ALvoid *data;
    ALboolean loop = AL_FALSE;
    alutLoadWAVFile((ALbyte *)"my_music.wav", &format, &data, &size, &freq, &loop);


    unsigned int alSource;      //source
    unsigned int alSampleSet;

    //create a source
    alGenSources(1, &alSource);

    //create  buffer
    alGenBuffers(1, &alSampleSet);

    //put the data into our sampleset buffer
    alBufferData(alSampleSet, format, data, size, freq);

    //assign the buffer to this source
    alSourcei(alSource, AL_BUFFER, alSampleSet);

    alSourcePlay(alSource);

    ALint source_state;
    alGetSourcei(alSource, AL_SOURCE_STATE, &source_state);

    std::cout<< AL_SOURCE_STATE << " .. " << source_state << "\n";
    // check for errors
    while (source_state == AL_PLAYING) {
        std::cout<< "playing";
            alGetSourcei(alSource, AL_SOURCE_STATE, &source_state);
            // check for errors
    }

    //release the data
    alutUnloadWAV(alFormatBuffer, alBuffer, alBufferLen, alFreqBuffer);

    //old
    alDeleteSources(1, &source);
    alcDestroyContext(context);
    alcCloseDevice(device);
    return 0;
}
