#!MC 1410

$!VARSET |PNG|=1
$!VARSET |max_step|=20

$!IF |PNG|==0
     $!EXPORTSETUP EXPORTFORMAT = AVI
     $!EXPORTSETUP IMAGEWIDTH = 806
     $!EXPORTSETUP EXPORTFNAME = 'animate_helmholtz.avi'
     $!EXPORTSTART             
       EXPORTREGION = ALLFRAMES 
$!ENDIF         

$!LOOP |max_step|

$!VARSET |step|=(|LOOP|-1)

$!READDATASET  '"helmholtz_animation0_frame|step|.dat" '
  READDATAOPTION = NEW
  RESETSTYLE = YES
  VARLOADMODE = BYNAME
  ASSIGNSTRANDIDS = YES
$!CREATEMIRRORZONES 
  SOURCEZONES =  [1-|NUMZONES|]
  MIRRORVARS =  [1]
$!GLOBALRGB REDCHANNELVAR = 3
$!GLOBALRGB GREENCHANNELVAR = 3
$!GLOBALRGB BLUECHANNELVAR = 3
$!SETCONTOURVAR 
  VAR = 3
  CONTOURGROUP = 1
  LEVELINITMODE = RESETTONICE
$!SETCONTOURVAR 
  VAR = 3
  CONTOURGROUP = 2
  LEVELINITMODE = RESETTONICE
$!SETCONTOURVAR 
  VAR = 3
  CONTOURGROUP = 3
  LEVELINITMODE = RESETTONICE
$!SETCONTOURVAR 
  VAR = 3
  CONTOURGROUP = 4
  LEVELINITMODE = RESETTONICE
$!SETCONTOURVAR 
  VAR = 3
  CONTOURGROUP = 5
  LEVELINITMODE = RESETTONICE
$!SETCONTOURVAR 
  VAR = 3
  CONTOURGROUP = 6
  LEVELINITMODE = RESETTONICE
$!SETCONTOURVAR 
  VAR = 3
  CONTOURGROUP = 7
  LEVELINITMODE = RESETTONICE
$!SETCONTOURVAR 
  VAR = 3
  CONTOURGROUP = 8
  LEVELINITMODE = RESETTONICE
$!FIELDLAYERS SHOWCONTOUR = YES
$!FIELDMAP [1-|NUMZONES|]  CONTOUR{CONTOURTYPE = BOTHLINESANDFLOOD}
$!FIELDMAP [1-|NUMZONES|]  CONTOUR{LINETHICKNESS = 0.400000000000000022}
$!TWODAXIS GRIDAREA{DRAWBORDER = YES}
$!REDRAWALL 
$!VIEW FIT
$!FIELDLAYERS SHOWEDGE = YES
$!REDRAWALL
$!TWODAXIS XDETAIL{TITLE{TITLEMODE = USETEXT}}
$!TWODAXIS XDETAIL{TITLE{TEXT = 'x<sub>1</sub>'}}
$!TWODAXIS YDETAIL{TITLE{TITLEMODE = USETEXT}}
$!TWODAXIS YDETAIL{TITLE{TEXT = 'x<sub>2</sub>'}}
$!REDRAWALL 
$!TWODAXIS XDETAIL{RANGEMIN = -5}
$!TWODAXIS XDETAIL{RANGEMAX = 5}
$!REDRAWALL 
$!TWODAXIS YDETAIL{RANGEMIN = -5}
$!TWODAXIS YDETAIL{RANGEMAX = 5}
$!REDRAWALL 
$!GLOBALCONTOUR 1  LEGEND{BOX{BOXTYPE = NONE}}
$!REDRAWALL 
$!TWODAXIS XDETAIL{TITLE{TEXTSHAPE{HEIGHT = 4.59999999999999964}}}
$!TWODAXIS XDETAIL{TITLE{TEXTSHAPE{HEIGHT = 5.59999999999999964}}}
$!REDRAWALL 
$!TWODAXIS YDETAIL{TITLE{TEXTSHAPE{HEIGHT = 4.59999999999999964}}}
$!TWODAXIS YDETAIL{TITLE{TEXTSHAPE{HEIGHT = 5.59999999999999964}}}
$!REDRAWALL 
$!TWODAXIS YDETAIL{TICKLABEL{TEXTSHAPE{HEIGHT = 4}}}
$!TWODAXIS YDETAIL{TICKLABEL{TEXTSHAPE{HEIGHT = 5}}}
$!TWODAXIS XDETAIL{TICKLABEL{TEXTSHAPE{HEIGHT = 4}}}
$!TWODAXIS XDETAIL{TICKLABEL{TEXTSHAPE{HEIGHT = 5}}}
$!REDRAWALL 
$!TWODAXIS XDETAIL{RANGEMAX = 6}
$!TWODAXIS XDETAIL{RANGEMAX = 7}
$!GLOBALCONTOUR 1  LEGEND{XYPOS{X = 89}}
$!GLOBALCONTOUR 1  LEGEND{SHOWHEADER = NO}
$!TWODAXIS XDETAIL{AUTOGRID = NO}
$!TWODAXIS XDETAIL{GRSPACING = 2}
$!GLOBALCONTOUR 1  LEGEND{NUMBERTEXTSHAPE{HEIGHT = 3.5}}
$!REDRAWALL 
$!CONTOURLEVELS DELETERANGE
  CONTOURGROUP = 1
  RANGEMIN = -0.01002
  RANGEMAX = 0.01402
$!CONTOURLEVELS NEW
  CONTOURGROUP = 1
  RAWDATA
11
-0.015
-0.012
-0.009
-0.006
-0.003
0
0.003
0.006
0.009
0.012
0.015

$!ATTACHTEXT 
  ANCHORPOS
    {    
    X = 36.67486331475128
    Y = 80.5455
    }
  TEXTSHAPE
    {
    FONT = HELV
    HEIGHT = 27
    }
  TEXT = '<greek>w</greek>t = |step|/|max_step|  x  2<greek>p</greek>'


$!REDRAWALL 

$!IF |PNG|==1
     $!EXPORTSETUP EXPORTFORMAT = PNG
     $!EXPORTSETUP IMAGEWIDTH = 2000
     $!EXPORTSETUP EXPORTFNAME = 'animate_helmholtz|step|.png'
     $!EXPORT
       EXPORTREGION = ALLFRAMES
$!ELSE
     $!EXPORTNEXTFRAME
$!ENDIF

$!ENDLOOP

$!IF |PNG|==0
$!EXPORTFINISH
$!ENDIF

