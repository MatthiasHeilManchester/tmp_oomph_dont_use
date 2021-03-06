#!MC 1000



$!VARSET |PNG|=1

$!FRAMELAYOUT SHOWHEADER = NO
$!FRAMELAYOUT SHOWBORDER = NO
$!FRAMECONTROL FITALLTOPAPER



$!PROMPTFORTEXTSTRING |NFILES|
  INSTRUCTIONS = "Enter the number of steps"

$!LOOP |NFILES|


$!VARSET |first_step|=0

$!VARSET |step|=|LOOP|
$!VARSET |step|+=|first_step|
$!VARSET |step|-=1

$!READDATASET "RESLT/soln|step|.dat"
$!FIELDLAYERS SHOWMESH = YES
$!FIELDLAYERS SHOWBOUNDARY = YES
$!FIELDLAYERS SHOWSHADE = YES
$!FIELDLAYERS SHOWCONTOUR = NO

$!FRAMELAYOUT SHOWHEADER = NO
$!FRAMELAYOUT SHOWBORDER = NO
$!FRAMECONTROL FITALLTOPAPER

$!VARSET |NORIG_ZONES|=|NUMZONES|

####################################################
# SCALING FACTOR FOR VELOCITY
####################################################
$!VARSET |VELOC_FACTOR|=0.5

####################################################
# NUMBER OF SLICES
####################################################
$!VARSET |NSLICE|=6


$!VARSET |FIRST_SLICE|=|NUMZONES|
$!VARSET |FIRST_SLICE|+=1
$!VARSET |LAST_SLICE|=|NUMZONES|
$!VARSET |LAST_SLICE|+=|NSLICE|

$!LOOP |NSLICE|

$!VARSET |ZSLICE|=|LOOP|
$!VARSET |ZSLICE|-=0.99


$!GLOBALTHREED 
  SLICE
  {
    ORIGIN{Z =|ZSLICE| }
    NORMAL
    {
      X=0
      Y=0
      Z=1
    }
  }
$!CREATESLICEZONEFROMPLANE 
  SLICESOURCE = VOLUMEZONES
  FORCEEXTRACTIONTOSINGLEZONE = YES

$!ENDLOOP




$!VARSET |ZONEMAX| = (|NUMZONES|-|NSLICE|)
$!ACTIVEFIELDZONES-=[1-|ZONEMAX|]
$!VARSET |ZONEMAX|+=1
$!ACTIVEFIELDZONES+=[|ZONEMAX|-|NUMZONES|]
$!ALTERDATA 
  EQUATION = 'V6=V3+|VELOC_FACTOR|*V6' 
$!FIELD 
  SHADE
  {
    SHOW = YES
  }
$!FIELD
  MESH
  {
    SHOW = NO    
    COLOR = BLACK
  }
$!FIELD
  BOUNDARY
  {
    SHOW = YES
    COLOR = BLACK
  }
$!THREEDAXIS
  ZDETAIL
  {
    VARNUM = 6
  }


$!THREEDVIEW VIEWERPOSITION{X = 16.457195465}
$!THREEDVIEW VIEWERPOSITION{Y = 21.3462401861}
$!THREEDVIEW VIEWERPOSITION{Z = 16.805042511}
$!THREEDVIEW PSIANGLE = 62
$!THREEDVIEW VIEWERPOSITION{X = 16.4815564968}
$!THREEDVIEW VIEWERPOSITION{Y = 21.3275699242}
$!THREEDVIEW THETAANGLE = -142.5
$!THREEDVIEW ALPHAANGLE = -109.1

$!FIELD [1-|NUMZONES|]  BOUNDARY{LINETHICKNESS = 0.1}
$!THREEDAXIS FRAMEAXIS{XYPOS{X = 83.999724254}}
$!THREEDAXIS FRAMEAXIS{XYPOS{Y = 72.014117553}}


$!CREATEMIRRORZONES 
  SOURCEZONES =  [|FIRST_SLICE|-|LAST_SLICE|]
  MIRRORVAR = 'X' 


$!CREATEMIRRORZONES 
  SOURCEZONES =  [|FIRST_SLICE|-|NUMZONES|]
  MIRRORVAR = 'Y' 

$!FIELD [1-|NUMZONES|]  MESH{SHOW = NO}
$!FIELD [1-|NUMZONES|]  BOUNDARY{COLOR = BLACK}
$!FIELD [1-|NUMZONES|]  BOUNDARY{LINETHICKNESS = 0.1}

$!THREEDAXIS XDETAIL{SHOWAXIS = NO}
$!THREEDAXIS YDETAIL{SHOWAXIS = NO}
$!THREEDAXIS ZDETAIL{SHOWAXIS = NO}
$!REDRAWALL 
$!THREEDVIEW 
  PSIANGLE = 76.1586
  THETAANGLE = -136.699
  ALPHAANGLE = -102.034
  VIEWERPOSITION
    {
    X = 19.3601776852
    Y = 20.5131589784
    Z = 9.62194566245
    }
$!VIEW PUSH
$!THREEDVIEW 
  PSIANGLE = 71.7911
  THETAANGLE = -140.93
  ALPHAANGLE = -107.151
  VIEWERPOSITION
    {
    X = 17.4566245818
    Y = 21.3875398437
    Z = 11.6964846811
    }

$!VIEW FIT
$!REDRAW



$!IF |PNG|==1


        $!EXPORTSETUP EXPORTFORMAT = PNG
        $!EXPORTSETUP IMAGEWIDTH = 600
        $!EXPORTSETUP USESUPERSAMPLEANTIALIASING = YES
        $!EXPORTSETUP SUPERSAMPLEFACTOR = 3
        $!EXPORTSETUP EXPORTFNAME = 'full_profiles|LOOP|.png'
        $!EXPORT
          EXPORTREGION = CURRENTFRAME

        $!EXPORTSETUP EXPORTFORMAT = EPS
        $!EXPORTSETUP IMAGEWIDTH = 1423
        $!EXPORTSETUP EXPORTFNAME = 'full_profiles|LOOP|.eps'

        $!EXPORTSETUP PRINTRENDERTYPE = IMAGE
        $!EXPORTSETUP EXPORTFNAME = 'full_profiles|LOOP|.img.eps'
        $!EXPORT
          EXPORTREGION = CURRENTFRAME

$!ELSE

        $!IF |LOOP|>1
                $!EXPORTNEXTFRAME
        $!ELSE

                $!EXPORTSETUP
                 EXPORTFORMAT = AVI
                 EXPORTFNAME = "full_profiles.avi"
                $!EXPORTSETUP IMAGEWIDTH = 829
                $!EXPORTSTART
        $!ENDIF

$!ENDIF


$!ENDLOOP



$!IF |PNG|==0
        $!EXPORTFINISH
$!ENDIF
