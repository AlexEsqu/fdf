# Fil de Fer - Wireframe

Projects elevation maps into a 3D height map, with modifiable projection type, color or elevation !
Done in C with homemade math and libc libraries, to get intimate with vectors and matrixes.

## Motivation

Who doesn't want to zoom past montains, and play with worlds at their commands ? This is the first step. 
I also discovered that my math teacher was right : I *will* need matrix transformation in my life.

## Requirement

* MinilibX, a lighter version of the X11 library
* Make
* GCC or Clang 

## Contributing

### Clone the repo

```bash
git clone https://github.com/AlexEsqu/fdf
cd fdf
```

### Build the project

```bash
make
```

### Run the project

```bash
./fdf ./test_maps/42.fdf
```