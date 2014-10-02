
all: robot.png

%.png: %.pov
	povray +I$< +UA +V +KFF5 +W600

clean:
	rm -f robot*.png
