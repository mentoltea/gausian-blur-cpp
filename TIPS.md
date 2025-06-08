# Some tips in image processing with gaussian blur
(in pseudocode)

- ## Increase contrast:
`image * gaus_blur(grayscale(image))`  

![contrast_input](examples/contrast_input.jpg)

![constrast](examples/constrast.jpg)

- ## Detect edge (DoG method):
```
g1 = gaus_blur(image, size, stdev)
g2 = gaus_blur(image, size+sizediff, stdev + stdiff)
mod = (g2 - g1).normalize
return mod
```

![edges_input](examples/edge_input.jpg)

![edges](examples/edge_output.jpg)  

The artifacts in the corner are caused by artifitial edge created by replacing non-existing pixels (pixels out of image) with solid color.
May consider using different method of out-of-image pixels interpolation.

For better effect, it is recommended to keep base convolution `size` at least 5-7 and `sizediff` 4-6. The bigger sizediff will better detect edges, but may lose information due to really small values before normalization.
`StDev` and `StDiff` determines both sensivity and lower&upper boundaries of detection. The bigger `StDiff` result in more noise. 

The image given in examples was processed by code (alg.cpp:algorytm):
```cpp
Image preprocess = gauss_blur(original, 13, 1); // to smooth artefacts of JPEG and prepare for image-detection

Image bw = to_grayscale(preprocess);

ColorRGBA missing_color(0.25,0.25,0.25); // out-of-image pixel values

int conv_size = 7;
int conv_size_diff = 5; // very important! without it, won't detect anything

double StBase = 1; // heavily determines the boundaries of resulting DoG
double StDiff = 0.95; // smaller -> sharper edges

Image g1 = gauss_blur(bw, conv_size, StBase, missing_color);
Image g2 = gauss_blur(bw, conv_size+conv_size_diff, StBase+StDiff, missing_color);

Image modified = g2 - g1;

ColorRGBA max_clr;
double k;

max_clr = get_color_at_int(modified, max(modified, to_gray));
k = to_gray(max_clr);
modified = (modified/k) * 2; // overflowing value > 1 to better highlight dark edges. later mapped to [0,255].

return modified;
```

### Keep in mind that DoG is most efficient on simplistic images

![sobx_input](examples/sobx.png)

![sobx_edges](examples/sobx_output.png)

In this example, the simplicity of the image `sizediff` can be set just to 1 and `size` to 4-5, making processing faster. Also, for the same reason the image is not preprocessed with gaussian blur.

Also the trick `modified = (g2 - g1)/2 + (g1 - g2)/2` is used to make result of DoG simmetrical (highlighting edges on both sides).

The image was processed with the following code:
```cpp
Image bw = to_grayscale(original);
ColorRGBA missing_color(1,1,1); // since the backcolor is white, expanding image with the same color will not create artifitial edge

int conv_size = 9; // can be really smallen down to 4-5
int conv_size_diff = 1;

double StBase = 0.75;
double StDiff = 0.1;

Image g1 = gauss_blur(bw, conv_size, StBase, missing_color);
Image g2 = gauss_blur(bw, conv_size+conv_size_diff, StBase+StDiff, missing_color);

Image modified = (g2 - g1)/2 + (g1 - g2)/2; // symmetric DoG

ColorRGBA max_clr;
double k;

max_clr = get_color_at_int(modified, max(modified, to_gray));
k = to_gray(max_clr);
modified = (modified/k);

modified = modified * 5; // very hard dark edge highlighting

return modified;
```