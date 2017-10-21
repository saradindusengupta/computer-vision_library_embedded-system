# Computer-vision_library_embedded-system


#  Aim and Scope of the project (in terms of specific physical achievement)

For the subsystems described in the summary sheet 7a, the aim is to provide algorithmic descriptions,
matlab codes, and corresponding c codes with library functions in the format of the interface to the
repository as per CDAC specifications. The subsystems consist of 1) Fundamental tools for image analysis,
2) Denoising filters, 3) Deblurring filters, and 4) Feature extraction using texture processing. A summary of
each subsystem is described in the following sections.
Fundamental tools for image analysis
This subsystem will consist of some advanced techniques for efficient processing and analysis of two
dimensional (2D) and three dimensional images (3D). Matlab, and C codes will be developed for image
processing tools that can be used for solving general image processing and analysis problems. A detailed
list of the tools is included in section

# 1.1 Image Enhancement
Images can be approximately represented using the linear degradation model
y = Af + w

where y denotes the observed image, f is the true image, A is the linear blur operator and w is the unknown
noise affecting the measurements. The recovery of f from the measurements y is an ill-posed problem [1].
The reasons for image degradation can be motion blurring, out of focus optics, light scattering etc. To
recover images from this degradation, image enhancement in the form of deblurring and denoising are
needed. In general, blind approaches for denoising and/or deblurring use image updation using diffusion [2-
8] and/or reverse diffusion [9-12] based approaches. In each of these methods, the updated image is
attempted to fit as closely as possible to the true denoised/deblurred image. At locations where the fitting is
not perfect, the updated image can have a speckled appearance. In this proposal, we will be providing the
algorithms along with c codes for the specific denoising and deblurring methods mentioned in sections
1.1.1 and 1.1.2.
# 1.1.1 Denoising
Denoising is the process of reconstructing the original image by removing unwanted noise from a corrupted
image. It is designed to suppress the noise, while preserving as many image structures and details as
possible. The main challenge is to design noise reduction filters that provide a compromise between these
two. The taxonomy of denoising methods in industrial imaging applications has evolved from the idea of
nonlinear edge preserved smoothing filters. These filters are derived using either optimization based or
diffusion based approaches. Of these, the former uses either distance based or energy based functional. In
the most elementary form, each of the above filtering method can be grouped into those based on Perona-
Malik diffusion, noise thresholding, Total Variational based diffusion, Non-Local diffusion, Mean
Curvature diffusion, Afine Invariant curvature motion, and Directional Anisotropic diffusion.
# 1.1.2 Deblurring
Blur is degradation of sharpness and contrast of the image, causing loss of high frequencies. The deblurring
performance is strongly linked to the denoising performance and vice versa. In spatial frequency domain, a
deblurring algorithm attempts to divide the image frequencies by those of the blurring kernel. Due to small
magnitudes of the blurring kernel at high frequencies, the high frequency noise in the image gets amplified
[9]. We will include those deblurring methods which can address this problem. The methods presented
include shock filter, complex shock filter, and non-locally stabilized reverse diffusion.

# 1.2 Feature Extraction using texture processing
In industrial applications, particularly fabric and paper industry texture represents a very useful feature
since it describes the micro-structural composition of the images. The problem of measuring texture leads
us to search for methods to describe texture. Instead of analyzing neighboring pixels, focus is shifted
towards neighboring regions. Finally, a comparison will be performed based on similarity and proximity of
local patterns. A generic feature extraction model to be followed in our algorithmic development in this
proposal is presented below.
Both statistical and structural approaches for textural feature extraction will be considered as part of this
proposal. Since, the structural approach treats texture as a set of primitive texels ordered in some regular or
repeated relationships, this will be particularly helpful in locating the primitives such as the basic elements
of a textile fabric or those of paper cloth. The loss of ordered relationship in a defective location can be
detected using the proposed algorithms. Statistical approach based on Julesz conjecture [13], can also be
used for feature extraction using texture processing. In this approach, texture represents a quantitative
measure of the arrangement of intensities in a region. It is more general and easy to compute, and therefore
more appealing for practical problems.
Description of the Project
2.1 Fundamental tools for image analysis
The following list includes the basic libraries to be developed in C.
```
Image Fusion
Image Transformations
Fourier Transform 
Haar Transform
Wavelet Transform
Bandlet Transform
Radon Transform
Hough Transform
```
```
1D and 2D histogram
Orthogonal Slicing
Removal of small structures
2D and 3D normalized cross-correlation
Vectorized Neighborhood calculations
Numerical derivative in Image space
Image gradient and directional derivatives
Hessian Matrix and Laplacian Operation
Gradient based corner detection
Differential structure measures for multispectral images
Diffusivity functions
```
# 2.2 Denoising
# 2.2.1 Perona-Malik Diffusion
Anisotropic diffusion filtering, proposed by Perona and Malik [14], is a promising technique because of its
simultaneous noise reduction and edge preserving properties. The smoothing process in this filter is
simulated as a diffusive process that is controlled by weighting the diffusion rate with an exponential
function of the signal intensity gradient. In Perona-Malik (PM) diffusion, the initial image u0 is modified
through the anisotropic diffusion equation Eq (2).
 ut  div ( g ( u )u)
u (0)  u 0
(2)
where div denotes the divergence operator, u is the smoothest image at time step t,
 u is gradient
magnitude of u, and
 g  u  is the diffusivity function. g(x) should be a non negative , monotonically
decreasing function approaching zero at infinity so that the diffusion process will take place only in the
interior of the region and will not affect edges, where the gradient magnitude is sufficiently large. In the
orthogonal decomposition of Perona-Malik diffusion [6], anisotropic diffusion becomes two 1-D evolutions
moving perpendicular to each other. In this, each component achieves smoothing along and perpendicular
to the edges.
# 2.2.2 Total Variational-based diffusion
Total Variational (TV) method originally proposed by Rudin, Osher and Fatemi is a denoising filter which
preserves the sharp edges. It is defined as an optimization problem based on minimizing energy functional
given by Eq (3).
E ( u )   u d

(3)
9
subjects to the two constraints
  ud   u 0
 d
 and
 u  u0   2 ,where u,u0 and σ2 are the true

 
image, the observed image, and the variance of the noise. Eq (3) is called the total variation of the image
u(x,y). Effectiveness of the TV method depends on choosing the value of smoothing parameter λ [15]. It
must be set low to remove noise, but at the cost of additional blur and loss of signal. Also, TV method can
sometimes introduce undesirable stair-casing effect [16].
2.2.3 Non-Local diffusion
Non-local diffusion equation [17] is given by
ut ( x, t ) 
  K ( y, x )u( y, t )dy  u ( x, t )
N
R
inR N X [0 , )
(4)
where K : R N XR N  R be a non-negative, smooth function such that
  K ( x, y ) dy  1 for all
 x  R N ,
N
Ru ( x, t) is density at the point x at time t, K(y,x) is probability distribution of jumping from location y to
location x, then
  K ( y, x) u( y, t )dy is the rate at which individuals are arriving to position x from all other
N
Rplaces.
2.2.4 Mean Curvature Diffusion
Mean curvature diffusion (MCD) is the evolution of an image defined in 3D Euclidean space at a rate
proportional to its mean curvature [18]. The surface evolves at a rate twice the mean curvature of the
image. The MCD removes the image noise via steepest descent surface area minimization. The mean
curvature diffusion equation is
1
 2 t I 
 ( I )
g
(5)
where I is the intensity of the image, g is the surface function defined in 3D Euclidean space. This equation
is equivalent to the scalar heat equation
 I  c( 2 I )
t (6)
where c is constant.
2.2.5 Affine Invariant Curvature Motion
An affine transformation maps disks into ellipses and rectangles into parallelograms [19]. Translation,
scaling, and shear are examples of general affine transformations. The curves evolving through the
evolution equation of the form
 I
 1
 k 3 I
t
(7)
Here I is the image whose level set curve has the curvature k given by
I I 2  2 I I I  I I 2
yy x x y xy xx y
k 
3
( I 2  I 2
 )
 2
x y (8)
The scale-space formed by this curve evolution provides an affine multi-resolution representation of planar
curves.
10
2.2.6 Directional Anisotropic Diffusion
Using directional anisotropic diffusion [20], the images are denoised by using a 3-D basis η, e1 and e2,
which corresponds respectively to unit vectors along directions of the gradient, the maximal and minimal
curvatures. The denoised image is obtained using
u  u   u   u   u (9)
0 1  2 e 1 3 e2
where u 0 is the noisy image, u is the denoised image, and u , u e1 and u e 2 are the directional derivatives of
image along directions of the gradient, maximum and minimum curvatures respectively. The
  ’s denote
the respective diffusivity functions.
2.3 Deblurring
2.3.1 Shock filter
Shock filter proposed by Rudin and Osher [21-22] is based on the idea of using a dilation process
near a maximum and an erosion process around a minimum. The decision whether a pixel belongs to the
influence zone of a maximum or a minimum is made on the basis of its Laplacian. It is proposed to sharpen
a blurred image. Shock filter processes each pixel P of an image I using the Partial differential equation
i(PDE) scheme, given at iteration by Eq (10)
I t ( P )  sign ( I t  1( P ))  I t 1( P ) , t  0
i i i(10)
With I o ( P i )  I ( P i ).  I (P i ) is the Laplacian computed at pixel P i , while I is the spatial gradient at P i .
At each iteration t ≥0 of this process, the shock filter performs morphological operators depending on the
sign of the Laplacian:
I t -1( P i )  0  I t ( P i )  I t 1 (P i )  D
I t -1( P )  0  I t ( P )  I t  1 ( P ) D
i i i(11)
Where D a disk-shaped structuring element of radius 1 is, while  and  are the symbols of classic dilation
and erosion operators. Shock filtering therefore produces such morphological processes of radius t near
minima and maxima during each iteration. This algorithm has been designed to create ruptures in inflection
zones, although it is not able to handle noise efficiently. The main drawback of shock filters is the
generation of sharp discontinuities at the borders between two regions.
2.3.2 Non-locally stabilized Reverse diffusion
In reverse diffusion, the image is enhanced by reversing time in the diffusion equation. This is numerically
achieved by subtracting the laplacian from the observed image. A deblurring method can restore structures
provided; they left a trace in the blurry image. In the generalized form, the deblurred image is constructed
with a constraint to have the same similarity degree of the blurred version. In [9], this is achieved using a
non-local deblurring functional
E (u)   ((u ( x)  NL U ( x)) 2   (k * u ( x)  u ( x)) 2 )dx
NL 0 0(12)
where the first term is viewed as an integral of the laplacian and the second term forces u to maintain the
same coherence as u0. Therefore, the latter act as a regularization term. The operator NL0 stands for Non-
local filtering operation; λ represents the Tikhonov regularization parameter, and k the Gaussian
convolution kernel.
11
# 2.4 Feature Extraction
# 2.4.1 Structural-based
Structural textures are characterized by a set of primitives (texels) and placement rules. The placement rules
define the spatial relationships between the texels and may be expressed in terms of adjacency, closest
distance or periodicities. The texels themselves may be defined by their gray level, shape or homogeneity
of some local property. A large number of woven fabrics are good examples of purely structural or semi-
deterministic textures. Microscopic images of electron beam textures in steel surface also have structural
characteristics. Thus, structural texture classification has many industrial applications, such as automatic
fabric inspection, steel surface testing.
We will implement a novel feature descriptor, called radon representation-based feature descriptor (RRFD),
that can handle unfavorable changes in illumination conditions, such as underexposure, and also the
variance caused by the geometric affine transformation. RRFD achieves both the geometric affine
transformation and the illumination change invariance in three steps. First, RRFD converts original pixel
represented images into Radon-pixel images by using the Radon transform. The new Radon representation
is more informative in geometry and has a much lower dimension. Second, RRFD projects an image from
the space of Radon-pixel pairs onto a feature space using Affine Invariant Transform. Finally, we will
define an illumination invariant distance metric on the feature space such that the affine invariance in
illumination is also achieved. Compared to Radon transform based methods [23-25], RRFD has several
advantages.
—It is able to handle the affine transformation in the geometry of texture.
—It is able to handle unfavorable change in illumination conditions, e.g., underexposure.
—It is easy to use. There are only two parameters in RRFD and neither of them needs careful adjustment.
Fig. 3 illustrates the RRFD scheme in which there are two input images and their similarity will be the
output.
# 2.4.2 Statistical-based
Statistical textural processing is illustrated in Fig.2. Here, a transformation T measures a statistical feature
1from the image region I (i, j ) and provides a scalar, vector, or matrix as output. In case of a matrix or vector
an additional transformation T2 is needed in order to compress the output of transformation T 1 . The goal is
to achieve a texture attribute A (i, j) that is a scalar and describes the texture in region I (i, j ). For this, two
statistical measures named first-order statistics and second-order statistics are used.
First-order statistics measure point properties and is determined by the pixel gray level which was
randomly hit and represents the probability distribution in terms of a histogram. In Fig.2, Y is the image
array and the transformation T2 computes a histogram, from which the scalar A representing the mean
value is easily found. Thus, the first-order probability distribution provides precise image information. Four
distinct transformations T 2 proposed for determining the texture attribute A are contrast, angular second
moment, entropy and mean. Second-order statistics capture the spatial relationship in a texture pattern and
provide information about the relative positions of various gray levels within the image. It is determined by
12
considering the gray levels at the two extremities of a randomly dropped line of varying length and
orientation. The four transformations listed for first-order statistics measure is applicable also here.

References
1.
 Stamatios Lefkimmiatis, Aurac lien Bourquard, and Michael Unser. Hessian Based Norm Regularization
for Image Restoration With Biomedical Applications. IEEE Tran. Image Processing March 2012 ; 21.

2.
 P. Perona and J. Malik. Scale space and edge detection using anisotropic diffusion, IEEE Trans. Pattern
Anal. Mach. Intell. 1990 ; 12:629-639.

3.
 P. Andrew, Witkin. Scale-space filtering Proc. Eighth Int. Joint Conf. On Artificial Intelligence 1983;
1019-1022.

4.
 D. Jiang, S. B. Fain, G. Tianliang, T. M. Grist and C. A. Mistretta. Noise Reduction in MR Angiography
with Non Linear Anisotropic Filtering. Journal of Magnetic Resonance Imaging May 2004 ; 19(5): 632-
639.
.

5.
 P .Thirion. Image matching as a diffusion process, an analogy with Maxwell’s demon, Medical Image
Analysis April1998; 2(3): 243-60.

6.
 Jose George and S. P. Indu. Fast Adaptive Anisotropic Filtering for Medical Image Enhancement. IEEE
Transaction On Medical Imaging 2008; 227-232.

7.
 Yu-Li You, Wenyuan Xu, Allen Tannenbaum, and MostafaKaveh. Behavioral Analysis of Anisotropic
Diffusion in Image Processing. IEEE Transactions On Image Processing November 1996 ; 5(11).

8.
 J. Michae Black, Sapiro Guillermo, H., Marimont David, and Heeger David. Robust Anisotropic Diffusion.
IEEE Transaction on Image Processing March 1998; 7(3): 421-432.

9.
 Buades, A.Coll, B., Morel, J.M. Image enhancement by non-local reverse heat equation. Technical Report
2006; CMLA.

10. V.P. Namboodiri and S. Chaudhuri. Image Restoration using Geometrically Stabilized Reverse Heat
Equation. International Conference on Image Processing 2006; 4:413-416.

11. S. Kindermann, S. Osher, Jones PW. Deblurring and Denoising of Images by Nonlocal Functionals,
Multiscale Modeling and Simulation;4:1091-1115.

12. I. Pollak, A.S.Willsky, and J. Krim, Image Segmentation and Edge Enhancement with Stabilized Inverse
Diffusion Equations. IEEE Trans. On Image Processing February 2000 ; 9(2):256-266.

13. M.D. Levine. Vision in Man and Machine. McGraw-Hill 1985.

14. Bernstein MA, Grgic M, Brosnan TJ, Pelc NJ. Reconstructions of phase contrast, phased array multi-coil
data, Magn Reson Med. 1994;32: 330-334.

15. U. M. Ascher, E. Haber, and H. Huang. On Effective Methods for Implicit Piecewise Smooth Surface
Recovery, Siam J. Sci. Comput, 2006;28(1): 339–358.

16. S. Wei and H. Xu. Staircasing reduction model applied to total variation based image reconstruction, 17th
European Signal Processing Conference (EUSIPCO, Glasgow, Scotland) 2009; 2579–2583.

17. Ronen Talmon, Sharon Gannot. Transient noise reduction using Nonlocal diffusion filters. IEEE Trans.
Audio Speech Language Proc. 2011;19(6):1584-1599.
