#!MC 1120

# Use png output (otherwise avi)
$!VARSET |PNG|=0






$!VARSET |nstep|=11
$!VARSET |lostep|=0
$!VARSET |dlstep|=1
$!LOOP |nstep|

$!VARSET |istep|=((|LOOP|-1)*|dlstep|+|lostep|)

# hierher $!DRAWGRAPHICS FALSE

$!NEWLAYOUT
$!PAPER SHOWPAPER = YES



$!LOOP 2
$!IF |LOOP|==1
#     $!VARSET |dir|='Validation/RESLT_proc0'
     $!VARSET |dir|='RESLT_proc0'
     $!VARSET |opt|='NEW'
     $!VARSET |lo|=1
$!ELSE
 #    $!VARSET |dir|='Validation/RESLT_proc1'
     $!VARSET |dir|='RESLT_proc1'
     $!VARSET |opt|='APPEND'
     $!VARSET |lo|=(|NUMZONES|+1)
$!ENDIF



$!READDATASET  '"|dir|/lagr|istep|.dat" '
  READDATAOPTION = |opt|
  RESETSTYLE = NO
  INCLUDETEXT = NO
  INCLUDEGEOM = NO
  INCLUDECUSTOMLABELS = NO
  VARLOADMODE = BYNAME
  ASSIGNSTRANDIDS = YES
  INITIALPLOTTYPE = CARTESIAN3D


$!GLOBALTHREEDVECTOR UVAR = 4
$!GLOBALTHREEDVECTOR VVAR = 5
$!GLOBALTHREEDVECTOR WVAR = 6
$!RESETVECTORLENGTH 
$!FIELDLAYERS SHOWVECTOR = YES
$!FIELDLAYERS SHOWMESH = NO
$!FIELDLAYERS SHOWEDGE = NO
$!FIELDMAP [|lo|-|NUMZONES|]  VECTOR{COLOR = RED}
$!FIELDMAP [|lo|-|NUMZONES|]  EDGELAYER{SHOW = NO}


$!VARSET |NTRACT|=(|NUMZONES|-|lo|+1)
$!VARSET |FIRST_SOLID|=(|NUMZONES|+1)


$!READDATASET  '"|dir|/soln|istep|.dat" '
  READDATAOPTION = APPEND
  RESETSTYLE = NO
  INCLUDETEXT = NO
  INCLUDEGEOM = NO
  INCLUDECUSTOMLABELS = NO
  VARLOADMODE = BYPOSITION
  ASSIGNSTRANDIDS = YES
  INITIALPLOTTYPE = CARTESIAN3D

$!VARSET |LAST_SOLID|=|NUMZONES|

$!ACTIVEFIELDMAPS += [|FIRST_SOLID|-|LAST_SOLID|]
$!FIELDMAP [|FIRST_SOLID|-|LAST_SOLID|]  VECTOR{COLOR = BLUE}
$!FIELDLAYERS SHOWEDGE = YES
$!THREEDAXIS AXISMODE = XYZDEPENDENT
$!GLOBALTHREED AXISSCALEFACT{Z = 1}
$!THREEDAXIS DEPXTOZRATIO = 1
$!RESET3DSCALEFACTORS 
$!VIEW FIT
$!FIELDLAYERS SHOWSHADE = YES
$!FIELDMAP [|FIRST_SOLID|-|LAST_SOLID|]  VECTOR{SHOW = NO}
$!IF |LOOP|==1
  $!FIELDMAP [|FIRST_SOLID|-|LAST_SOLID|]  EDGELAYER{COLOR = BLUE}
$!ELSE
  $!FIELDMAP [|FIRST_SOLID|-|LAST_SOLID|]  EDGELAYER{COLOR = CYAN}
$!ENDIF
$!FIELDLAYERS USETRANSLUCENCY = YES
$!GLOBALTHREEDVECTOR RELATIVELENGTH = 1

$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 1.1
$!VIEW SETMAGNIFICATION
  MAGNIFICATION = 1
$!THREEDVIEW 
  PSIANGLE = 73.164
  THETAANGLE = 218.753
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 12.26961650481291
    Y = 15.28616047992647
    Z = 6.002351050659371
    }
$!VIEW PUSH



$!VARSET |FIRST_EXACT|=(|NUMZONES|+1)
$!LOOP |NTRACT|

  $!VARSET |src_zone|=(|lo|-1+|LOOP|) 
  $!DUPLICATEZONE 
    SOURCEZONE = |src_zone|

$!ENDLOOP
$!VARSET |LAST_EXACT|=|NUMZONES|


$!IF |LOOP|==1
   $!FIELDMAP [|FIRST_EXACT|-|LAST_EXACT|]  EDGELAYER{COLOR = GREEN}
   $!FIELDMAP [|FIRST_EXACT|-|LAST_EXACT|]  EDGELAYER{LINETHICKNESS = 2.5}
$!ELSE
   $!FIELDMAP [|FIRST_EXACT|-|LAST_EXACT|]  EDGELAYER{COLOR = YELLOW}     
   $!FIELDMAP [|FIRST_EXACT|-|LAST_EXACT|]  EDGELAYER{LINETHICKNESS = 0.8}  
$!ENDIF

$!FIELDMAP [|FIRST_EXACT|-|LAST_EXACT|]  VECTOR{SHOW = NO}

$!ALTERDATA [|FIRST_EXACT|-|LAST_EXACT|] 
  EQUATION = 'v1=v7'
$!ALTERDATA [|FIRST_EXACT|-|LAST_EXACT|] 
  EQUATION = 'v2=v8'
$!ALTERDATA [|FIRST_EXACT|-|LAST_EXACT|] 
  EQUATION = 'v3=v9'


$!REDRAWALL
#$!PAUSE "bla"

$!ENDLOOP

$!IF |PNG|==1


        $!EXPORTSETUP EXPORTFORMAT = PNG
        $!EXPORTSETUP IMAGEWIDTH = 750
        $!EXPORTSETUP EXPORTFNAME = 'block|LOOP|.png'
        $!EXPORT
          EXPORTREGION = ALLFRAMES

$!ELSE

        $!IF |LOOP|>1
                $!EXPORTNEXTFRAME
        $!ELSE

                $!EXPORTSETUP
                  EXPORTREGION = ALLFRAMES
                  EXPORTFORMAT = AVI
                  EXPORTFNAME = "block.avi"
                $!EXPORTSETUP IMAGEWIDTH = 750
                $!EXPORTSTART
        $!ENDIF

$!ENDIF


$!ENDLOOP


$!IF |PNG|==0
        $!EXPORTFINISH
$!ENDIF

