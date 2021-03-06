#!MC 1120


$!VARSET |loframe|=0
$!VARSET |nframe|=40
$!VARSET |dframe|=1


$!VARSET |step|=0
$!VARSET |u_min|=-2
$!VARSET |u_max|=2


$!VARSET |postfix|=".plt"
$!VARSET |postfix|=".dat"
$!VARSET |PNG|=1
$!VARSET |dir|="Validation/RESLT_adapt_0" 


$!NEWLAYOUT 
$!IF |PNG|==0
     $!EXPORTSETUP EXPORTFORMAT = AVI
     $!EXPORTSETUP IMAGEWIDTH = 806
     $!EXPORTSETUP EXPORTFNAME = 'helmholtz_validate_animation.avi'
     $!EXPORTSTART             
       EXPORTREGION = ALLFRAMES 
$!ENDIF             

$!LOOP |nframe|

$!VARSET |frame|=(|loframe|+(|loop|-1)*|dframe|)
$!NEWLAYOUT 
$!DRAWGRAPHICS FALSE


$!DRAWGRAPHICS FALSE
$!READDATASET  '"|dir|/helmholtz_animation|step|_frame|frame||postfix|" '
  READDATAOPTION = NEW
  RESETSTYLE = YES
  INCLUDETEXT = YES
  INCLUDEGEOM = NO
  INCLUDECUSTOMLABELS = NO
  VARLOADMODE = BYNAME
  ASSIGNSTRANDIDS = YES
  INITIALPLOTTYPE = CARTESIAN3D
$!FIELDLAYERS SHOWSCATTER = YES
$!FIELDLAYERS SHOWSCATTER = NO
$!FIELDLAYERS SHOWMESH = NO
$!FIELDLAYERS SHOWSHADE = YES
$!FIELDMAP [1-|NUMZONES|]  EDGELAYER{COLOR = RED}
$!FIELDMAP [1-|NUMZONES|]  EDGELAYER{LINETHICKNESS = 0.1}

$!VARSET |LAST_FE|=|NUMZONES|

$!CREATERECTANGULARZONE 
  IMAX = 10
  JMAX = 10
  KMAX = 10
  X1 = |MINX|
  Y1 = |MINY|
  Z1 = |u_min|
  X2 = |MAXX|
  Y2 = |MAXY|
  Z2 = |u_max|
  XVAR = 1
  YVAR = 2
  ZVAR = 3



$!ACTIVEFIELDMAPS += [|NUMZONES|]
$!VIEW AXISNICEFIT
  AXIS = 'Z'
  AXISNUM = 1
$!RESET3DAXES 
$!VIEW FIT
$!FIELDLAYERS USETRANSLUCENCY = YES
$!ACTIVEFIELDMAPS -= [|NUMZONES|]




$!VARSET |FIRST_EXACT|=(|NUMZONES|+1)
$!READDATASET  '"|dir|/exact_helmholtz_animation|step|_frame|frame||postfix|" '
  READDATAOPTION = APPEND
  RESETSTYLE = NO
  INCLUDETEXT = YES
  INCLUDEGEOM = NO
  INCLUDECUSTOMLABELS = NO
  VARLOADMODE = BYNAME
  ASSIGNSTRANDIDS = YES
  INITIALPLOTTYPE = CARTESIAN3D
$!VARSET |LAST_EXACT|=|NUMZONES|

$!ACTIVEFIELDMAPS += [|FIRST_EXACT|-|LAST_EXACT|]
$!FIELDMAP [|FIRST_EXACT|-|LAST_EXACT|]  EDGELAYER{COLOR = GREEN}
$!FIELDMAP [|FIRST_EXACT|-|LAST_EXACT|]  EDGELAYER{LINETHICKNESS = 0.1}



$!FIELDMAP [1-|NUMZONES|]  CONTOUR{SHOW = NO}
$!ALTERDATA 
  EQUATION = 'v4=v3'


$!VARSET |first_contour|=(|NUMZONES|+1)

$!LOOP |LAST_FE|
 $!DUPLICATEZONE 
   SOURCEZONE = |LOOP|
$!ENDLOOP

$!ALTERDATA  [|first_contour|-|NUMZONES|]
  EQUATION = 'v3=|u_min|'

$!FIELDMAP [|first_contour|-|NUMZONES|] EDGELAYER{COLOR = BLACK}
$!FIELDMAP [|first_contour|-|NUMZONES|] EDGELAYER{LINETHICKNESS = 0.02}
$!GLOBALCONTOUR 1  VAR = 4
$!FIELDLAYERS SHOWCONTOUR = YES
$!CONTOURLEVELS NEW
  CONTOURGROUP = 1
  RAWDATA
15
-2
-1.71428571429
-1.42857142857
-1.14285714286
-0.857142857143
-0.571428571429
-0.285714285714
0
0.285714285714
0.571428571429
0.857142857143
1.14285714286
1.42857142857
1.71428571429
2  


$!THREEDAXIS XDETAIL{TITLE{TITLEMODE = USETEXT}}
$!THREEDAXIS XDETAIL{TITLE{TEXT = 'x'}}
$!THREEDAXIS YDETAIL{TITLE{TITLEMODE = USETEXT}}
$!THREEDAXIS YDETAIL{TITLE{TEXT = 'y'}}
$!THREEDAXIS ZDETAIL{TITLE{TITLEMODE = USETEXT}}
$!THREEDAXIS ZDETAIL{TITLE{TEXT = '<greek>f</greek>(x,y,t)'}}

$!THREEDAXIS XDETAIL{TITLE{TEXTSHAPE{HEIGHT = 8.60000000000000142}}}
$!THREEDAXIS YDETAIL{TITLE{TEXTSHAPE{HEIGHT = 8.60000000000000142}}}
$!THREEDAXIS ZDETAIL{TITLE{TEXTSHAPE{HEIGHT = 8.60000000000000142}}}


$!THREEDAXIS XDETAIL{TICKLABEL{TEXTSHAPE{HEIGHT = 9}}}
$!THREEDAXIS YDETAIL{TICKLABEL{TEXTSHAPE{HEIGHT = 9}}}
$!THREEDAXIS ZDETAIL{TICKLABEL{TEXTSHAPE{HEIGHT = 9}}}

$!THREEDAXIS XDETAIL{TITLE{OFFSET = 20}}
$!THREEDAXIS YDETAIL{TITLE{OFFSET = 20}}
$!THREEDAXIS ZDETAIL{TITLE{OFFSET = 20}}

$!THREEDAXIS XDETAIL{AUTOGRID = NO}
$!THREEDAXIS XDETAIL{GRSPACING = 1}
$!THREEDAXIS YDETAIL{AUTOGRID = NO}
$!THREEDAXIS YDETAIL{GRSPACING = 1}
$!THREEDAXIS ZDETAIL{AUTOGRID = NO}
$!THREEDAXIS ZDETAIL{GRSPACING = 1}
$!THREEDAXIS FRAMEAXIS{SHOW = NO}


###################################################

$!DRAWGRAPHICS TRUE
$!REDRAWALL


$!IF |PNG|==1
     $!EXPORTSETUP EXPORTFORMAT = PNG
     $!EXPORTSETUP IMAGEWIDTH = 600
     $!EXPORTSETUP EXPORTFNAME = 'helmholtz_validate_animation|loop|.png'
     $!EXPORT
       EXPORTREGION = ALLFRAMES
$!ELSE
     $!EXPORTNEXTFRAME
$!ENDIF

$!ENDLOOP

$!IF |PNG|==0
$!EXPORTFINISH
$!ENDIF
