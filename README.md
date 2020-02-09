<h1 align="center">Welcome to Functional Images  👋</h1>

In some applications, it is much better than classic bitmaps that describe
the view of each pixel is a vector image. The idea is to describe the image
using mathematical objects, e.g. vectors or curves, which can be adapted
scale freely and easily apply some transformations.

Even more generalized concept of the image are so-called functional images
functional images), which are functions R^2 -> A, where A in a special case can be a set of colors.
### Demo
* Rotated vertical stripe with colors caribbean blue and blue
<img align="center" width="350px" src= "/img/rotate.bmp">

* Polar checker with colors caribbean blue and blue and 4 parts
<img align="center" width="350px" src= "/img/polar_checker.bmp">

<br>

### Tech
* [C++17] - Project was written in CPP17 standard, especially using functional and meta programming.
* [Doxygen] - All methods in main files (`images.hpp` and `functional.hpp`) were documented.
* [Unit Tests] - Stored in `test` folder, maintained by `CMake`.

### Usage

```bash
$ git clone https://github.com/mvxxx/functional-images.git
$ cd functional-images
$ mkdir build
$ cd build
$ cmake ..
$ make
```

`fun-image-lib` is static library, you can link that to your files. As an example, the `example.cpp` is used for demo.

### Supported Images
There are pre-created functional images types. Of course, in use of them you can create much more.

| Type | README |
| ------ | ------ |
| constant | makes const functional image |
| rotate | rotates image with given angle |
| translate | moves image with given vector |
| scale | scales image with given factor |
| circle | draws circle with given params |
| vertical_stripe | draws vertical stripe |
| checker | draws checker with given params |
| polar_checker | draws polar checker |
| rings | draws rings with given params |
| cond | makes conditional image |
| lerp | makes linear interpolation |
| darken | makes img darker |
| lighten | makes img lighter |


### Development

Want to contribute? Great!
Just make a proposal by creating pull request.

### License
[MIT](https://choosealicense.com/licenses/mit/)
