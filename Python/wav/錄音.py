import pyaudio
import time
import threading
import wave


class Recorder():
    def __init__(self, chunk=1024, channels=1, rate=64000):
        self.CHUNK = chunk
        self.FORMAT = pyaudio.paInt16
        self.CHANNELS = channels
        self.RATE = rate
        self._running = True
        self._frames = []

    def start(self):
        threading._start_new_thread(self.__recording, ())

    def __recording(self):
        self._running = True
        self._frames = []
        p = pyaudio.PyAudio()
        stream = p.open(format=self.FORMAT, channels=self.CHANNELS, rate=self.RATE, input=True,
                        frames_per_buffer=self.CHUNK)
        while (self._running):
            data = stream.read(self.CHUNK)
            self._frames.append(data)

        stream.stop_stream()
        stream.close()
        p.terminate()

    def stop(self):
        self._running = False

    def save(self, filename):

        p = pyaudio.PyAudio()
        if not filename.endswith(".wav"):
            filename = filename + ".wav"
        wf = wave.open(filename, 'wb')
        wf.setnchannels(self.CHANNELS)
        wf.setsampwidth(p.get_sample_size(self.FORMAT))
        wf.setframerate(self.RATE)
        wf.writeframes(b''.join(self._frames))
        wf.close()
        print("Saved")


if __name__ == "__main__":

    for i in range(1, 4):
        a = int(input('請輸入相應數字開始:'))
        if a == 1:
            rec = Recorder()
            begin = time.time()
            print("Start recording")
            rec.start()
            b = int(input('請輸入相應數字停止:'))
            if b == 2:
                print("Stop recording")
                rec.stop()
                fina = time.time()
                t = fina - begin
                print('錄音時間為%ds' % t)
                rec.save("1_%d.wav" % i)