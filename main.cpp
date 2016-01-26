#include <AL/al.h>
#include <AL/alc.h>
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

    alDeleteSources(1, &source);
    alcDestroyContext(context);
    alcCloseDevice(device);
    return 0;
}
