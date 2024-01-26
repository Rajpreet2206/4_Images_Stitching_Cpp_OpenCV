CC = g++
PROJECT = new_output
#SRC = stitching_direct.cpp
#SRC = two_images_direct_stitch.cpp
SRC = read_and_save.cpp
#SRC = check_code.cpp
#SRC = single_camera_check.cpp
LIBS = `pkg-config --cflags --libs opencv4` -pthread

$(PROJECT) : $(SRC)
	$(CC) $(SRC) -o $(PROJECT) $(LIBS)