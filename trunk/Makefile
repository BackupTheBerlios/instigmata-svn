TARGET=instigmata
OBJECTS=main.o box.o player.o button.o looper.o image.o selectgroup.o \
		loader.o soundcore.o soundplayer.o sampledir.o eventbutton.o \
		soundlooper.o barcounter.o slider.o dualslider.o logconv.o \
		logger.o peakmeter.o distortion.o slicer.o

CXXFLAGS=`allegro-config --cflags` -I./fmodapi/inc -march=i686 -g
LDFLAGS=`allegro-config --libs --static` fmodapi/lib/libfmodex.so
CXX=g++


$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(CXXFLAGS) $(LDFLAGS) -o $@

.cpp.o: 
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f $(OBJECTS) $(TARGET) core core.*

.PHONY: clean
