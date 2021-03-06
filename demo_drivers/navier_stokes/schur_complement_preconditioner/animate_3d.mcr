#!MC 1120

$!VARSET |NSOL|=12
$!VARSET |DIR|="Validation/RESLT_three_d_fp"


$!EXPORTSETUP EXPORTFORMAT = AVI
$!EXPORTSETUP IMAGEWIDTH = 806
$!EXPORTSETUP EXPORTFNAME = 'animate_3d.avi'
$!VARSET |IS_OPEN|=0



$!LOOP  |NSOL|


$!DRAWGRAPHICS NO

$!VARSET |STEP|=(|LOOP|-1)

$!READDATASET  '"|DIR|/soln|STEP|.dat" '
  READDATAOPTION = NEW
  RESETSTYLE = YES
  INCLUDETEXT = NO
  INCLUDEGEOM = NO
  INCLUDECUSTOMLABELS = NO
  VARLOADMODE = BYNAME
  ASSIGNSTRANDIDS = YES
  INITIALPLOTTYPE = CARTESIAN3D

$!FIELDLAYERS SHOWMESH = NO
$!FIELDMAP [1-|NUMZONES|]  EDGELAYER{COLOR = BLACK}
$!FIELDMAP [1-|NUMZONES|]  EDGELAYER{LINETHICKNESS = 0.0200000000000000004}
$!REDRAWALL 
$!GLOBALCONTOUR 1  VAR = 7
$!CONTOURLEVELS RESETTONICE
  CONTOURGROUP = 1
  APPROXNUMVALUES = 15
$!FIELDLAYERS SHOWCONTOUR = YES
$!REDRAWALL 
$!GLOBALTHREEDVECTOR UVAR = 4
$!GLOBALTHREEDVECTOR VVAR = 5
$!GLOBALTHREEDVECTOR WVAR = 6
$!RESETVECTORLENGTH 
$!FIELDLAYERS SHOWVECTOR = YES
$!FIELDMAP [1-|NUMZONES|]  VECTOR{COLOR = BLACK}
$!FIELDLAYERS USETRANSLUCENCY = YES

$!THREEDVIEW 
  PSIANGLE = 68.0637
  THETAANGLE = 20.8887
  ALPHAANGLE = 1.35317
  VIEWERPOSITION
    {
    X = -2.894176530613343
    Y = -8.393710522813635
    Z = 4.333769021970101
    }
$!VIEW PUSH
$!VIEW FIT
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 1.1


$!IF |IS_OPEN|==0
$!EXPORTSTART 
  EXPORTREGION = CURRENTFRAME
$!VARSET |IS_OPEN|=1
$!ENDIF

$!DRAWGRAPHICS TRUE
$!REDRAWALL 
$!EXPORTNEXTFRAME 


$!ENDLOOP

$!EXPORTFINISH 
