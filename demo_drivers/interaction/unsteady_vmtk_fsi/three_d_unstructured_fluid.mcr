#!MC 1100

$!VARSET |lostep|=0
$!VARSET |nstep|=160
$!VARSET |dstep|=1

$!VARSET |PNG|=0
$!VARSET |potential|=0

$!NEWLAYOUT 

$!IF |PNG|==0
     $!EXPORTSETUP EXPORTFORMAT = AVI
     $!EXPORTSETUP IMAGEWIDTH = 806
     $!EXPORTSETUP EXPORTFNAME = 'unstructured_fluid.avi'
     $!EXPORTSTART 
       EXPORTREGION = CURRENTFRAME
$!ENDIF

$!LOOP |nstep|

$!VARSET |step|=(|lostep|+(|loop|-1)*|dstep|)

$!DRAWGRAPHICS FALSE

$!READDATASET  '"RESLT/fluid_soln|step|.dat" ' 
  READDATAOPTION = NEW
  RESETSTYLE = YES
  INCLUDETEXT = NO
  INCLUDEGEOM = NO
  INCLUDECUSTOMLABELS = NO
  VARLOADMODE = BYNAME
  ASSIGNSTRANDIDS = YES
  INITIALPLOTTYPE = CARTESIAN3D
  VARNAMELIST = '"V1" "V2" "V3" "V4" "V5" "V6" "V7"' 
$!FIELDLAYERS SHOWMESH = NO
$!GLOBALCONTOUR 1  VAR = 7
$!CONTOURLEVELS RESETTONICE
  CONTOURGROUP = 1
  APPROXNUMVALUES = 15
$!FIELDLAYERS SHOWCONTOUR = YES
$!FIELDMAP [1-|NUMZONES|]  EDGELAYER{EDGETYPE = BORDERSANDCREASES}
$!FIELDMAP [1-|NUMZONES|]  EDGELAYER{COLOR = BLACK}
$!FIELDMAP [1-|NUMZONES|]  EDGELAYER{LINETHICKNESS = 0.1}
$!GLOBALTHREEDVECTOR UVAR = 4
$!GLOBALTHREEDVECTOR VVAR = 5
$!GLOBALTHREEDVECTOR WVAR = 6
$!RESETVECTORLENGTH 
$!FIELDLAYERS SHOWVECTOR = YES
$!FIELDMAP [1-|NUMZONES|]  VECTOR{COLOR = BLUE}
$!GLOBALTHREEDVECTOR RELATIVELENGTH = 0.1 # adjust 50
$!FIELDLAYERS USETRANSLUCENCY = YES
$!THREEDAXIS XDETAIL{SHOWAXIS = NO}
$!THREEDAXIS YDETAIL{SHOWAXIS = NO}
$!THREEDAXIS ZDETAIL{SHOWAXIS = NO}


$!IF |potential|==1

        $!CREATERECTANGULARZONE 
          IMAX = 2
          JMAX = 2
          KMAX = 2
          X1 = -1
          Y1 = -1
          Z1 = -1
          X2 = 1
          Y2 = 1
          Z2 = 2
          XVAR = 1
          YVAR = 2
          ZVAR = 3

$!ELSE

        $!CREATERECTANGULARZONE 
          IMAX = 2
          JMAX = 2
          KMAX = 2
          X1 = -1.5
          Y1 = -3
          Z1 = -1
          X2 = 1.5
          Y2 = 5
          Z2 = 12
          XVAR = 1
          YVAR = 2
          ZVAR = 3


$!ENDIF



$!ACTIVEFIELDMAPS += [|NUMZONES|]

$!FIELDMAP [|NUMZONES|]  SHADE{SHOW = NO}
$!FIELDMAP [|NUMZONES|]  CONTOUR{SHOW = NO}
$!FIELDMAP [|NUMZONES|]  EDGELAYER{COLOR = BLUE}
$!ACTIVEFIELDMAPS -= [|NUMZONES|]


#$!ATTACHTEXT 
#  ANCHORPOS
#    {
#    X = 25.44169611307421
#    Y = 89.59294984029967
#    }
#  TEXTSHAPE
#    {
#    FONT = HELV
#    HEIGHT = 12
#    }
#  TEXT = 'step:  |step|' 


$!GLOBALTHREED 
  LIGHTSOURCE
    {
    XYZDIRECTION
      {
      X = 0.365062340002
      Y = -0.718592964824
      Z = 0.591906782203
      }
    }

$!THREEDVIEW 
  PSIANGLE = 53.3526
  THETAANGLE = -142.475
  ALPHAANGLE = -114.878
  VIEWERPOSITION
    {
    X = 48.29171454607098
    Y = 63.20869499734915
    Z = 64.3718545640057
    }

$!VIEW FIT

$!THREEDAXIS FRAMEAXIS{SHOW = NO}


$!CONTOURLEVELS NEW
  CONTOURGROUP = 1
  RAWDATA
18
-650
-563.352941176
-476.705882353
-390.058823529
-303.411764706
-216.764705882
-130.117647059
-43.4705882353
43.1764705882
129.823529412
216.470588235
303.117647059
389.764705882
476.411764706
563.058823529
649.705882353
736.352941176
823

#$!VIEW TRANSLATE
#  X = -10
#  Y = 0

$!DRAWGRAPHICS TRUE
$!REDRAWALL


$!IF |PNG|==1
     $!EXPORTSETUP EXPORTFORMAT = PNG
     $!EXPORTSETUP IMAGEWIDTH = 600
     $!EXPORTSETUP EXPORTFNAME = 'unstructured_fluid|loop|.png'
     $!EXPORT
       EXPORTREGION = ALLFRAMES
$!ELSE
     $!EXPORTNEXTFRAME
$!ENDIF

$!ENDLOOP

$!IF |PNG|==0
$!EXPORTFINISH
$!ENDIF
