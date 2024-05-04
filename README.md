# 115kaudio
1 bit ADC that frames result as serial data. Play the audio with a lowpass on TxD.

"OMG it ****ing works"

credits to @LOOKMUMNOCMPUTR for the song, I think its halariously ironic to do this with 
his work, given the nature of how it was built. (I didn't ask, so, if your there, tell me if you need a takedown, 
I should hope your cool given the nature of this hack, this is the first 8N1 1 bit audio stream ever made, cause nobody was stupid enough to try it yet :] )

I will be posting the circuit that built the audio data stream. which is just a tiny13 and a few RC filters.

This is the concept, I used the comparitor in the tiny13, and not the uart, as you need to realtime output the bits.
![noalt](p1310446.jpg)


To regenerate the audio you just need to recreate the lowpass that the ADC used.
![noalt](p1310471.jpg)

Be aware that the levels comming out of this are 3V, which is REALLY hot for an audio signal, you will want to make sure that either the volume of what you play it to is quite far down, or that you use a voltage divider to scale it a bit.


I'm on linux,
I use minicom to set the baud rate of the port to 115200 8N1,
then the binary can just be cat'd to the port

cat song.bin > /dev/ttyUSB1

GEEK OUT!


Rue
