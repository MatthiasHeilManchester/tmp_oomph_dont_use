#!MC 1000

$!VARSET |PNG|=1


#$!GETUSERINPUT |lostep| INSTRUCTIONS = "Loop. First Step??"
$!VARSET  |lostep|=0
#$!GETUSERINPUT |dlstep| INSTRUCTIONS = "Loop. Step Increment?"
$!VARSET  |dlstep|=1
#$!GETUSERINPUT |nstep| INSTRUCTIONS = "Loop. Number of Steps??"
$!VARSET |nstep| = 40

$!LOOP |nstep|
$!VarSet |nnstep| = |LOOP|
$!VarSet |nnstep| -= 1
$!VarSet |iistep| = |dlstep|
$!VarSet |iistep| *= |nnstep|
$!VarSet |iistep| += |lostep|
$!NEWLAYOUT
$!DRAWGRAPHICS FALSE
#    $!IF |iistep| < 10 
#      $!VARSET |istep|='00|iistep|'
#    $!ENDIF
#    $!IF |iistep| > 9 
#      $!VARSET |istep|='0|iistep|'
#    $!ENDIF
#    $!IF |iistep| > 99 
#      $!VARSET |istep|=|iistep|
#    $!ENDIF
$!VARSET |istep|=|iistep|
#$!VARSET |istep|+=1
#$!VARSET |istep|*=10

$!DRAWGRAPHICS FALSE



$!VarSet |LFDSFN1| = '"RESLT_CR/Wall|istep|.dat"'
$!VarSet |LFDSVL1| = '"V1" "V2"'
$!VarSet |LFDSFN2| = '"RESLT_CR/soln|istep|.dat"'
$!VarSet |LFDSVL2| = '"x" "y"'
$!SETSTYLEBASE FACTORY
$!PAPER 
  BACKGROUNDCOLOR = WHITE
  ISTRANSPARENT = YES
  ORIENTPORTRAIT = NO
  SHOWGRID = YES
  SHOWRULER = YES
  SHOWPAPER = YES
  PAPERSIZE = A4
  PAPERSIZEINFO
    {
    A3
      {
      WIDTH = 11.693
      HEIGHT = 16.535
      }
    A4
      {
      WIDTH = 8.2677
      HEIGHT = 11.693
      LEFTHARDCLIPOFFSET = 0.125
      RIGHTHARDCLIPOFFSET = 0.125
      TOPHARDCLIPOFFSET = 0.125
      BOTTOMHARDCLIPOFFSET = 0.125
      }
    }
  RULERSPACING = ONECENTIMETER
  PAPERGRIDSPACING = ONETENTHCENTIMETER
  REGIONINWORKAREA
    {
    X1 = -0.05
    Y1 = -0.05
    X2 = 11.74
    Y2 = 8.318
    }
$!COLORMAP 
  CONTOURCOLORMAP = SMRAINBOW
$!COLORMAPCONTROL RESETTOFACTORY
### Frame Number 1 ###
$!READDATASET  '|LFDSFN1|' 
  INITIALPLOTTYPE = CARTESIAN2D
  INCLUDETEXT = NO
  INCLUDEGEOM = NO
  VARLOADMODE = BYNAME
  VARNAMELIST = '|LFDSVL1|' 
$!REMOVEVAR |LFDSVL1|
$!REMOVEVAR |LFDSFN1|
$!RENAMEDATASETVAR 
  VAR = 1
  NAME = 'x' 
$!RENAMEDATASETVAR 
  VAR = 2
  NAME = 'y' 
$!READDATASET  '|LFDSFN2|' 
  INITIALPLOTTYPE = CARTESIAN2D
  INCLUDETEXT = YES
  INCLUDEGEOM = YES
  READDATAOPTION = APPEND
  RESETSTYLE = NO
  VARLOADMODE = BYNAME
  VARNAMELIST = '|LFDSVL2|' 
$!REMOVEVAR |LFDSVL2|
$!REMOVEVAR |LFDSFN2|
$!FRAMELAYOUT 
  SHOWBORDER = NO
  SHOWHEADER = NO
  HEADERCOLOR = RED
  XYPOS
    {
    X = 0.125
    Y = 0.20954
    }
  WIDTH = 11.443
  HEIGHT = 7.8486
$!PLOTTYPE  = CARTESIAN2D
$!FRAMENAME  = 'Frame 001' 
$!ACTIVEFIELDZONES  =  [1]
$!GLOBALRGB 
  RANGEMIN = 0
  RANGEMAX = 1
$!GLOBALCONTOUR  1
  LEGEND
    {
    XYPOS
      {
      X = 95
      }
    }
  COLORMAPFILTER
    {
    CONTINUOUSCOLOR
      {
      CMIN = 0
      CMAX = 1
      }
    }
$!GLOBALCONTOUR  2
  LEGEND
    {
    XYPOS
      {
      X = 95
      }
    }
  COLORMAPFILTER
    {
    CONTINUOUSCOLOR
      {
      CMIN = 0
      CMAX = 1
      }
    }
$!GLOBALCONTOUR  3
  LEGEND
    {
    XYPOS
      {
      X = 95
      }
    }
  COLORMAPFILTER
    {
    CONTINUOUSCOLOR
      {
      CMIN = 0
      CMAX = 1
      }
    }
$!GLOBALCONTOUR  4
  LEGEND
    {
    XYPOS
      {
      X = 95
      }
    }
  COLORMAPFILTER
    {
    CONTINUOUSCOLOR
      {
      CMIN = 0
      CMAX = 1
      }
    }
$!GLOBALSCATTER 
  LEGEND
    {
    XYPOS
      {
      X = 95
      }
    }
  REFSCATSYMBOL
    {
    COLOR = RED
    FILLCOLOR = RED
    }
$!FIELD  [1]
  MESH
    {
    COLOR = RED
    }
  CONTOUR
    {
    CONTOURTYPE = FLOOD
    COLOR = RED
    USELIGHTINGEFFECT = YES
    }
  VECTOR
    {
    COLOR = RED
    }
  SCATTER
    {
    COLOR = RED
    }
  SHADE
    {
    COLOR = WHITE
    }
  BOUNDARY
    {
    SHOW = YES
    COLOR = BLACK
    LINETHICKNESS = 0.8
    }
  POINTS
    {
    POINTSTOPLOT = SURFACENODES
    }
  SURFACES
    {
    SURFACESTOPLOT = JPLANES
    }
  VOLUMEMODE
    {
    VOLUMEOBJECTSTOPLOT
      {
      SHOWISOSURFACES = NO
      SHOWSLICES = NO
      SHOWSTREAMTRACES = NO
      }
    }



$!FIELD  [2-|NUMZONES|]
  MESH
    {
    COLOR = RED
    }
  CONTOUR
    {
    CONTOURTYPE = FLOOD
    COLOR = RED
    USELIGHTINGEFFECT = YES
    }
  VECTOR
    {
    COLOR = RED
    }
  SCATTER
    {
    COLOR = RED
    }
  SHADE
    {
    COLOR = WHITE
    }
  BOUNDARY
    {
    SHOW = YES
    COLOR = RED
    }
  POINTS
    {
    POINTSTOPLOT = SURFACENODES
    }
  SURFACES
    {
    SURFACESTOPLOT = KPLANES
    }
  VOLUMEMODE
    {
    VOLUMEOBJECTSTOPLOT
      {
      SHOWISOSURFACES = NO
      SHOWSLICES = NO
      SHOWSTREAMTRACES = NO
      }
    }
$!TWODAXIS 
  XDETAIL
    {
    VARNUM = 1
    }
  YDETAIL
    {
    VARNUM = 2
    }
$!VIEW FIT
$!TWODAXIS 
  DEPXTOYRATIO = 1
$!TWODAXIS 
  XDETAIL
    {
    RANGEMIN = 0
    RANGEMAX = 2.1301466288470334298
    GRSPACING = 0.2
    }
$!TWODAXIS 
  YDETAIL
    {
    RANGEMIN = 0
    RANGEMAX = 1.499999999999999778
    GRSPACING = 0.2
    }
$!GLOBALISOSURFACE 
  MARCHINGCUBEALGORITHM = CLASSICPLUS
$!GLOBALSLICE 
  BOUNDARY
    {
    SHOW = NO
    }
$!FIELDLAYERS 
  SHOWMESH = NO

$!SETSTYLEBASE CONFIG


############################







$!IF |PNG|==1


        $!EXPORTSETUP EXPORTFORMAT = PNG
        $!EXPORTSETUP SUPERSAMPLEFACTOR = 3
        $!EXPORTSETUP USESUPERSAMPLEANTIALIASING = YES
        $!EXPORTSETUP IMAGEWIDTH = 600
        $!EXPORTSETUP EXPORTFNAME = 'wall|istep|.png'
        $!EXPORT
          EXPORTREGION = CURRENTFRAME

        $!EXPORTSETUP EXPORTFORMAT = EPS
        $!EXPORTSETUP USESUPERSAMPLEANTIALIASING = NO
        $!EXPORTSETUP IMAGEWIDTH = 1423
        $!EXPORTSETUP EXPORTFNAME = 'wall|istep|.eps'

        $!EXPORTSETUP PRINTRENDERTYPE = IMAGE
        $!EXPORTSETUP EXPORTFNAME = 'wall|istep|.img.eps'
        $!EXPORT
          EXPORTREGION = CURRENTFRAME

$!ELSE

        $!IF |LOOP|>1
                $!EXPORTNEXTFRAME
        $!ELSE

                $!EXPORTSETUP
                 EXPORTFORMAT = AVI
                 EXPORTFNAME = "wall.avi"
                $!EXPORTSETUP IMAGEWIDTH = 829
                $!EXPORTSETUP USESUPERSAMPLEANTIALIASING = NO
                $!EXPORTSTART
        $!ENDIF

$!ENDIF


$!VARSET |LAST_STEP|=|istep|

$!EndLoop

$!FIELDLAYERS SHOWBOUNDARY = NO
$!REDRAWALL



$!VARSET |STEP|=|LAST_STEP|
$!VARSET |STEP|+=1


$!IF |PNG|==1


        $!EXPORTSETUP EXPORTFORMAT = PNG
        $!EXPORTSETUP IMAGEWIDTH = 600
        $!EXPORTSETUP SUPERSAMPLEFACTOR = 3
        $!EXPORTSETUP USESUPERSAMPLEANTIALIASING = YES
        $!EXPORTSETUP EXPORTFNAME = 'wall|STEP|.png'
        $!EXPORT
          EXPORTREGION = CURRENTFRAME

        $!EXPORTSETUP EXPORTFORMAT = EPS
        $!EXPORTSETUP IMAGEWIDTH = 1423
        $!EXPORTSETUP USESUPERSAMPLEANTIALIASING = NO
        $!EXPORTSETUP EXPORTFNAME = 'wall|STEP|.eps'

        $!EXPORTSETUP PRINTRENDERTYPE = IMAGE
        $!EXPORTSETUP EXPORTFNAME = 'wall|STEP|.img.eps'
        $!EXPORT
          EXPORTREGION = CURRENTFRAME

$!ELSE

        $!IF |STEP|>1
                $!EXPORTNEXTFRAME
        $!ELSE

                $!EXPORTSETUP
                 EXPORTFORMAT = AVI
                 EXPORTFNAME = "wall.avi"
                $!EXPORTSETUP IMAGEWIDTH = 829
                $!EXPORTSETUP USESUPERSAMPLEANTIALIASING = NO
                $!EXPORTSTART
        $!ENDIF

$!ENDIF




$!IF |PNG|==0
        $!EXPORTFINISH
$!ENDIF


$!QUIT

