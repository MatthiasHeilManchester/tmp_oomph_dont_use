#!MC 1120


$!VARSET |nstep|=21
$!VARSET |ampl|=0.3
$!VARSET |PNG|=1

$!NEWLAYOUT 
$!VARSET |new_frame_done|=0


$!IF |PNG|==0
     $!EXPORTSETUP EXPORTFORMAT = AVI
     $!EXPORTSETUP IMAGEWIDTH = 806
     $!EXPORTSETUP EXPORTFNAME = 'animate_displacement.avi'
     $!EXPORTSTART             
       EXPORTREGION = ALLFRAMES 
$!ENDIF         

$!READDATASET  '"Validation/RESLT_adaptive_unstructured/elast_soln2.dat" '
#$!READDATASET  '"RESLT/elast_soln0.dat" '
  READDATAOPTION = NEW
  RESETSTYLE = YES
  INCLUDETEXT = NO
  INCLUDEGEOM = NO
  INCLUDECUSTOMLABELS = NO
  VARLOADMODE = BYNAME
  ASSIGNSTRANDIDS = YES
  INITIALPLOTTYPE = CARTESIAN2D

    
$!VARSET |old|=|NUMZONES|
$!VARSET |new|=(|NUMZONES|+1)
$!CREATEMIRRORZONES 
  SOURCEZONES =  [1-|NUMZONES|]
$!FIELDMAP [|new|-|NUMZONES|]  SHADE{SHOW = NO}
$!FIELDLAYERS SHOWEDGE = YES
$!FIELDMAP [1-|old|]  EDGELAYER{SHOW = NO}



$!LOOP |nstep|

$!DRAWGRAPHICS FALSE

$!VARSET |phi|=(2.0*3.14158*(|LOOP|-1)/(|nstep|-1))
$!VARSET |step|=(|LOOP|-1)
$!VARSET |max_step|=(|nstep|-1)


$!TWODAXIS GRIDAREA{DRAWBORDER = YES}
$!TWODAXIS XDETAIL{TITLE{TITLEMODE = USETEXT}}
$!TWODAXIS XDETAIL{TITLE{TEXT = 'r'}}
$!TWODAXIS YDETAIL{TITLE{TITLEMODE = USETEXT}}
$!TWODAXIS YDETAIL{TITLE{TEXT = 'z'}}
$!FIELDLAYERS SHOWSHADE = YES
$!FIELDLAYERS SHOWEDGE = NO
$!FIELDLAYERS SHOWMESH = NO
$!FIELDMAP [1-|old|]  SHADE{COLOR = CUSTOM10}
$!ALTERDATA 
  EQUATION = 'v9=v3*cos(|phi|)-v6*sin(|phi|)'
$!ALTERDATA 
  EQUATION = 'v10=v4*cos(|phi|)-v7*sin(|phi|)'
$!ALTERDATA 
  EQUATION = 'v11=v1+|ampl|*v9'
$!ALTERDATA 
  EQUATION = 'v12=v2+|ampl|*v10'

$!ALTERDATA [|new|-|NUMZONES|]
  EQUATION = 'v9=v3*cos(|phi|)-v6*sin(|phi|)'
$!ALTERDATA  [|new|-|NUMZONES|]
  EQUATION = 'v10=v4*cos(|phi|)-v7*sin(|phi|)'
$!ALTERDATA  [|new|-|NUMZONES|]
  EQUATION = 'v11=v1-|ampl|*v9'
$!ALTERDATA  [|new|-|NUMZONES|]
  EQUATION = 'v12=v2+|ampl|*v10'


$!IF |new_frame_done|==0

$!FRAMELAYOUT ISTRANSPARENT = YES
$!LINKING BETWEENFRAMES{LINKFRAMESIZEANDPOSITION = YES}
$!LINKING BETWEENFRAMES{LINKXAXISRANGE = YES}
$!LINKING BETWEENFRAMES{LINKYAXISRANGE = YES}
$!LINKING BETWEENFRAMES{LINKAXISPOSITION = YES}
$!PICK ADDALL
  SELECTFRAMES = YES
$!PICK COPY
$!PICK PASTE
$!VARSET |new_frame_done|=1

$!ENDIF

$!TWODAXIS XDETAIL{VARNUM = 11}
$!TWODAXIS YDETAIL{VARNUM = 12}
$!FIELDMAP [1-|old|]  SHADE{COLOR = BLUE}
#$!IF |new_frame_done|==0
$!FRAMECONTROL PUSHTOP
$!FRAMELAYOUT ISTRANSPARENT = NO
$!FRAMECONTROL PUSHTOP
#$!ENDIF
$!TWODAXIS YDETAIL{RANGEMIN = -1.2}
$!TWODAXIS YDETAIL{RANGEMAX = 1.2}
$!TWODAXIS XDETAIL{RANGEMIN = -1.3}
$!TWODAXIS XDETAIL{RANGEMAX = 1.3}
$!ATTACHTEXT 
  ANCHORPOS
    {
    X = 36.67486331475128
    Y = 54.54545454545454
    }
  TEXTSHAPE
    {
    FONT = HELV
    HEIGHT = 27
    }
  TEXT = 'bla'
$!PICK ADDALL
  SELECTTEXT = YES
$!PICK CUT
$!ATTACHTEXT 
  ANCHORPOS
    {
    X = 36.67486331475128
    Y = 54.54545454545454
    }
  TEXTSHAPE
    {
    FONT = HELV
    HEIGHT = 27
    }
  TEXT = '<greek>w</greek>t = |step|/|max_step|  x  2<greek>p</greek>'

$!FIELDLAYERS SHOWEDGE = YES

###################################################

$!DRAWGRAPHICS TRUE
$!REDRAWALL


$!IF |PNG|==1
     $!EXPORTSETUP EXPORTFORMAT = PNG
     $!EXPORTSETUP IMAGEWIDTH = 2000
     $!EXPORTSETUP EXPORTFNAME = 'animate_displacement|step|.png'
     $!EXPORT
       EXPORTREGION = ALLFRAMES
$!ELSE
     $!EXPORTNEXTFRAME
$!ENDIF

$!ENDLOOP

$!IF |PNG|==0
$!EXPORTFINISH
$!ENDIF
