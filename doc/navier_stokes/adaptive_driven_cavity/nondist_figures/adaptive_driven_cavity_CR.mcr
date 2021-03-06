#!MC 1000

$!DRAWGRAPHICS FALSE


$!READDATASET  '"soln1.dat" ' 
  READDATAOPTION = NEW
  RESETSTYLE = YES
  INCLUDETEXT = NO
  INCLUDEGEOM = NO
  INCLUDECUSTOMLABELS = NO
  VARLOADMODE = BYNAME
  INITIALPLOTTYPE = CARTESIAN3D
  VARNAMELIST = '"V1" "V2" "V3" "V4" "V5"' 

$!THREEDVIEW 
  PSIANGLE = 65.6726
  THETAANGLE = 303.735
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 11.0022443003
    Y = -6.51346768001
    Z = 6.15012571252
    }
$!VIEW PUSH
$!THREEDVIEW 
  PSIANGLE = 57.2772
  THETAANGLE = 344.805
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 3.55617151812
    Y = -10.7521965483
    Z = 7.932790819
    }
$!VIEW PUSH
$!FIELDLAYERS SHOWMESH = NO
$!FIELDLAYERS SHOWBOUNDARY = NO
$!FIELDLAYERS SHOWBOUNDARY = YES
$!FIELDLAYERS SHOWSHADE = YES
$!FIELD [1-|NUMZONES|]  BOUNDARY{COLOR = RED}
$!FIELD [1-|NUMZONES|]  BOUNDARY{LINETHICKNESS = 0.02}
$!REDRAWALL 
$!PICK SETMOUSEMODE
  MOUSEMODE = SELECT
$!FRAMELAYOUT WIDTH = 5.5
$!FRAMELAYOUT HEIGHT = 4.4
$!FRAMELAYOUT XYPOS{X = 0}
$!FRAMELAYOUT XYPOS{Y = 0}
$!FRAMELAYOUT ISTRANSPARENT = YES
$!REDRAWALL 
$!LINKING BETWEENFRAMES{LINK3DVIEW = YES}
$!VIEW FIT
$!THREEDVIEW 
  PSIANGLE = 61.4561
  THETAANGLE = 8.02094
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = -1.07705497388
    Y = -10.6916522437
    Z = 6.58855951514
    }
$!VIEW PUSH
$!THREEDVIEW 
  PSIANGLE = 54.9555
  THETAANGLE = -20.7672
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 4.23490473119
    Y = -9.34916280244
    Z = 7.8285906
    }
$!VIEW PUSH
$!THREEDVIEW 
  PSIANGLE = 56.8128
  THETAANGLE = -35.1613
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 6.70076898221
    Y = -8.30275433144
    Z = 7.48331346963
    }
$!VIEW PUSH
$!ATTACHTEXT 
  ANCHORPOS
    {
    X = 11.4729241877
    Y = 89.2130614698
    }
  TEXTSHAPE
    {
    FONT = HELV
    HEIGHT = 22
    }
  TEXT = 'u(x,y)' 
$!PICK SETMOUSEMODE
  MOUSEMODE = SELECT
$!FRAMELAYOUT XYPOS{X = 0.1}
$!FRAMELAYOUT XYPOS{Y = 0.1}
$!FRAMELAYOUT XYPOS{Y = 0.12}
$!PICK ADDALL
  SELECTFRAMES = YES
$!PICK COPY
$!PICK PASTE
$!PICK PASTE
$!PICK PASTE
$!PICK ADD
  X = 1.85115523466
  Y = 0.152151662351
$!FRAMELAYOUT XYPOS{X = 5.6}
$!FRAMECONTROL POPATPOSITION
  X = 2.88685920578
  Y = 4.49853541119
$!PICK ADD
  X = 2.88685920578
  Y = 4.49853541119
$!FRAMELAYOUT XYPOS{Y = 4.5}
$!FRAMELAYOUT HEIGHT = 4
$!FRAMELAYOUT HEIGHT = 3.6
$!FRAMECONTROL POPATPOSITION
  X = 4.27725631769
  Y = 0.152151662351
$!PICK ADD
  X = 4.27725631769
  Y = 0.152151662351
$!FRAMELAYOUT HEIGHT = 3.4
$!FRAMELAYOUT HEIGHT = 3.8
$!FRAMECONTROL POPATPOSITION
  X = 1.79440433213
  Y = 4.48451481846
$!PICK ADD
  X = 1.79440433213
  Y = 4.48451481846
$!FRAMECONTROL POPATPOSITION
  X = 5.59671480144
  Y = 5.98471824144
$!PICK ADD
  X = 5.59671480144
  Y = 5.98471824144
$!FRAMELAYOUT HEIGHT = 3.68
$!FRAMELAYOUT XYPOS{Y = 4}
$!PICK ADD
  X = 5.52577617329
  Y = 4.54059718941
$!PICK ADD
  X = 5.42646209386
  Y = 3.96575288714
$!PICK ADD
  X = 0.106064981949
  Y = 3.96575288714
$!PICK ADD
  X = 0.233754512635
  Y = 3.93771170167
$!FRAMECONTROL POPATPOSITION
  X = 0.134440433213
  Y = 0.78307833557
$!PICK ADD
  X = 0.134440433213
  Y = 0.78307833557
$!FRAMELAYOUT HEIGHT = 3.8
$!FRAMELAYOUT XYPOS{Y = 4}
$!FRAMELAYOUT XYPOS{X = 5}
$!FRAMELAYOUT XYPOS{X = 5.6}
$!PICK ADD
  X = 6.81685920578
  Y = 6.76987143478
$!VIEW FIT
$!FRAMECONTROL POPATPOSITION
  X = 11.0731768953
  Y = 1.84864338367
$!PICK ADD
  X = 11.0731768953
  Y = 1.84864338367
$!FRAMELAYOUT HEIGHT = 3.8
$!FRAMECONTROL POPATPOSITION
  X = 4.27725631769
  Y = 2.73194072618
$!PICK ADD
  X = 4.27725631769
  Y = 2.73194072618
$!VIEW FIT
$!FRAMECONTROL POPATPOSITION
  X = 6.57566787004
  Y = 1.8206021982
$!PICK ADD
  X = 6.57566787004
  Y = 1.8206021982
$!VIEW FIT
$!PICK ADD
  X = 6.51891696751
  Y = 0.3905017389
$!PICK CLEAR
$!ATTACHTEXT 
  ANCHORPOS
    {
    X = 11.4729241877
    Y = 89.2130614698
    }
  TEXTSHAPE
    {
    FONT = HELV
    HEIGHT = 22
    }
  TEXT = 'v(x,y)' 
$!PICK ADD
  X = 6.80267148014
  Y = 2.99833198821
$!PICK SETMOUSEMODE
  MOUSEMODE = SELECT
$!PICK ADD
  X = 7.42693140794
  Y = 1.87668456915
$!PICK ADD
  X = 7.42693140794
  Y = 1.87668456915
$!THREEDAXIS ZDETAIL{VARNUM = 4}
$!FRAMECONTROL POPATPOSITION
  X = 3.9225631769
  Y = 4.97523556429
$!PICK ADD
  X = 3.9225631769
  Y = 4.97523556429
$!PICK ADD
  X = 1.34039711191
  Y = 4.33028829833
$!PICK CLEAR
$!ATTACHTEXT 
  ANCHORPOS
    {
    X = 11.4729241877
    Y = 89.2130614698
    }
  TEXTSHAPE
    {
    FONT = HELV
    HEIGHT = 22
    }
  TEXT = 'p(x,y)' 
$!THREEDVIEW 
  PSIANGLE = 67.8935
  THETAANGLE = 310.9
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 9.28630730311
    Y = -7.11099979989
    Z = 4.68943160821
    }
$!VIEW PUSH
$!THREEDVIEW 
  PSIANGLE = 61.8573
  THETAANGLE = 334.581
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 5.2488327488
    Y = -9.49239043286
    Z = 5.88564296125
    }
$!VIEW PUSH
$!THREEDAXIS ZDETAIL{VARNUM = 5}
$!VIEW FIT
$!FRAMECONTROL POPATPOSITION
  X = 4.27725631769
  Y = 0.979366633905
$!LINKING BETWEENFRAMES{LINK3DVIEW = NO}
$!VIEW FIT
$!VIEW AXISNICEFIT
  AXIS = 'Z' 
  AXISNUM = 1
$!THREEDAXIS AXISMODE = XYZDEPENDENT
$!RESET3DSCALEFACTORS 
$!THREEDVIEW 
  PSIANGLE = 50.7135
  THETAANGLE = 331.795
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 6.40843728195
    Y = -10.5168250431
    Z = 10.6679384864
    }
$!VIEW PUSH
$!THREEDVIEW 
  PSIANGLE = 58.607
  THETAANGLE = 322.044
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 8.97994506858
    Y = -10.3710492198
    Z = 8.8542105804
    }
$!VIEW PUSH
$!VIEW FIT
$!FRAMECONTROL POPATPOSITION
  X = 7.93768953069
  Y = 2.84410546809
$!LINKING BETWEENFRAMES{LINK3DVIEW = NO}
$!VIEW FIT
$!THREEDAXIS AXISMODE = XYZDEPENDENT
$!VIEW FIT
$!THREEDAXIS DEPXTOZRATIO = 1
$!VIEW FIT
$!THREEDVIEW 
  PSIANGLE = 73.9298
  THETAANGLE = 326.687
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = -2.51798505858
    Y = 5.0922244196
    Z = 5.58501170463
    }
$!VIEW PUSH
$!VIEW FIT
$!THREEDVIEW 
  PSIANGLE = 63.7146
  THETAANGLE = 325.294
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 13.8269691754
    Y = -18.7425132821
    Z = 6.29805664369
    }
$!VIEW PUSH
$!VIEW FIT
$!THREEDVIEW 
  PSIANGLE = 64.6433
  THETAANGLE = 319.258
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 6.97986412571
    Y = -7.02240010138
    Z = 5.24252246973
    }
$!VIEW PUSH
$!PICK SETMOUSEMODE
  MOUSEMODE = SELECT
$!THREEDAXIS ZDETAIL{VARNUM = 2}
$!VIEW FIT
$!THREEDVIEW 
  PSIANGLE = 55.8211
  THETAANGLE = 233.358
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 8.81184076475
    Y = 6.68240782465
    Z = 7.53440113829
    }
$!VIEW PUSH
$!THREEDAXIS ZDETAIL{VARNUM = 4}
$!THREEDVIEW 
  PSIANGLE = 38.1767
  THETAANGLE = 337.367
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 3.48436251166
    Y = -6.6577727024
    Z = 9.83083394602
    }
$!VIEW PUSH
$!THREEDVIEW 
  PSIANGLE = 53.9638
  THETAANGLE = 321.58
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 6.80489932786
    Y = -7.44902107457
    Z = 7.34894077263
    }
$!VIEW PUSH
$!VIEW FIT
$!FIELDLAYERS USETRANSLUCENCY = YES
$!REDRAWALL 
$!FIELDLAYERS USETRANSLUCENCY = NO
$!REDRAWALL 
$!THREEDVIEW 
  PSIANGLE = 51.6421
  THETAANGLE = 44.694
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = -6.42055093253
    Y = -6.49487127381
    Z = 7.75490355558
    }
$!VIEW PUSH
$!THREEDVIEW 
  PSIANGLE = 54.4281
  THETAANGLE = 19.6204
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = -2.92727735328
    Y = -9.11407246476
    Z = 7.26743580584
    }
$!VIEW PUSH
$!FRAMECONTROL POPATPOSITION
  X = 2.6314801444
  Y = 3.12451732285
$!THREEDVIEW 
  PSIANGLE = 62.3216
  THETAANGLE = 48.8729
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = -8.75443721692
    Y = -7.58086470776
    Z = 6.88509851846
    }
$!VIEW PUSH
$!THREEDVIEW 
  PSIANGLE = 53.0351
  THETAANGLE = 19.6204
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = -3.22220347814
    Y = -9.94138839044
    Z = 8.78324177171
    }
$!VIEW PUSH
$!FRAMECONTROL POPATPOSITION
  X = 1.14176895307
  Y = 5.45193571739
$!THREEDVIEW 
  PSIANGLE = 54.4281
  THETAANGLE = 322.973
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = 8.41135961694
    Y = -9.98832532834
    Z = 9795.49620051
    }
$!VIEW PUSH
$!THREEDVIEW 
  PSIANGLE = 48.8562
  THETAANGLE = 34.0145
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = -6.30410980845
    Y = -9.58200066371
    Z = 11069.5136799
    }
$!VIEW PUSH
$!FRAMECONTROL POPATPOSITION
  X = 7.82418772563
  Y = 6.08286239061
$!PICK SETMOUSEMODE
  MOUSEMODE = SELECT
$!PLOTTYPE = CARTESIAN2D
$!GLOBALCONTOUR 1  VAR = 5
$!CONTOURLEVELS RESETTONICE
  CONTOURGROUP = 1
  APPROXNUMVALUES = 15
$!FIELDLAYERS SHOWCONTOUR = YES
$!PICK SETMOUSEMODE
  MOUSEMODE = SELECT
$!FIELD [1-|NUMZONES|]  BOUNDARY{COLOR = BLACK}
$!REDRAWALL 
$!GLOBALTWODVECTOR UVAR = 3
$!GLOBALTWODVECTOR VVAR = 4
$!RESETVECTORLENGTH 
$!FIELDLAYERS SHOWVECTOR = YES
$!STREAMTRACE ADD
  STREAMTYPE = TWODLINE
  STARTPOS
    {
    X = 0.549782178823
    Y = 0.851379726909
    }
$!STREAMTRACE ADD
  STREAMTYPE = TWODLINE
  STARTPOS
    {
    X = 0.506138193983
    Y = 0.319444859336
    }
  ALTSTARTPOS
    {
    X = 0.549782178823
    Y = 0.851379726909
    }
$!PICK SETMOUSEMODE
  MOUSEMODE = SELECT
$!STREAMTRACE DELETERANGE
  RANGESTART = 2
  RANGEEND = 2
$!STREAMTRACE DELETERANGE
  RANGESTART = 1
  RANGEEND = 1
$!STREAMTRACE ADD
  STREAMTYPE = TWODLINE
  DIRECTION = BOTH
  STARTPOS
    {
    X = 0.607974158608
    Y = 0.755535606626
    }
  ALTSTARTPOS
    {
    X = 0.506138193983
    Y = 0.319444859336
    }
$!STREAMTRACE ADD
  STREAMTYPE = TWODLINE
  DIRECTION = BOTH
  STARTPOS
    {
    X = 0.554631510471
    Y = 0.477587657804
    }
  ALTSTARTPOS
    {
    X = 0.607974158608
    Y = 0.755535606626
    }
$!STREAMTRACE ADD
  STREAMTYPE = TWODLINE
  DIRECTION = BOTH
  STARTPOS
    {
    X = 0.578878168715
    Y = 0.247561769123
    }
  ALTSTARTPOS
    {
    X = 0.554631510471
    Y = 0.477587657804
    }
$!STREAMTRACE ADD
  STREAMTYPE = TWODLINE
  DIRECTION = BOTH
  STARTPOS
    {
    X = 0.617672821905
    Y = 0.0894189706555
    }
  ALTSTARTPOS
    {
    X = 0.578878168715
    Y = 0.247561769123
    }
$!REDRAWALL 
$!STREAMTRACE ADD
  STREAMTYPE = TWODLINE
  DIRECTION = BOTH
  STARTPOS
    {
    X = 0.215178295057
    Y = 0.87534075698
    }
  ALTSTARTPOS
    {
    X = 0.617672821905
    Y = 0.0894189706555
    }
$!STREAMTRACE ADD
  STREAMTYPE = TWODLINE
  DIRECTION = BOTH
  STARTPOS
    {
    X = 0.583727500364
    Y = 0.621353838229
    }
  ALTSTARTPOS
    {
    X = 0.215178295057
    Y = 0.87534075698
    }
$!REDRAWALL 
$!FIELDLAYERS SHOWVECTOR = NO
$!REDRAWALL 
$!GLOBALSTREAM MAXSTEPS = 10000
$!REDRAWALL 
$!STREAMTRACE SETTERMINATIONLINE
  RAWDATA
2
0.617672821905 0.750743400612
0.0212050291054 0.980769289292
$!GLOBALSTREAM TERMLINE{ISACTIVE = YES}
$!REDRAW 
$!STREAMTRACE SETTERMINATIONLINE
  RAWDATA
2
0.627371485203 0.736366782569
0.835892746101 0.118172206741
$!REDRAW 
$!GLOBALSTREAM TERMLINE{SHOW = NO}
$!FIELD [1-|NUMZONES|]  BOUNDARY{COLOR = RED}
$!REDRAWALL 
$!PICK SETMOUSEMODE
  MOUSEMODE = SELECT
$!PICK ADD
  X = 6.71754512635
  Y = 4.30224711286
$!PICK CLEAR
$!ATTACHTEXT 
  ANCHORPOS
    {
    X = 11.4729241877
    Y = 89.2130614698
    }
  TEXTSHAPE
    {
    FONT = HELV
    HEIGHT = 22
    }
  TEXT = 'streamlines and pressure contours' 
$!PICK ADD
  X = 6.54729241877
  Y = 4.30224711286
$!PICK SHIFT
  X = -0.354693140794
  Y = -0.070102963691
$!REDRAW 
$!PICK ADD
  X = 10.122599278
  Y = 5.80245053585
$!GLOBALCONTOUR 1  LEGEND{SHOW = YES}
$!REDRAWALL 
$!PICK ADD
  X = 10.2786642599
  Y = 6.08286239061
#$!PICK SHIFT
#  X = -0.439819494585
#  Y = 0.406597189408
$!PICK ADD
  X = 10.0090974729
  Y = 6.46141839454
$!GLOBALCONTOUR 1  LEGEND{NUMBERTEXTSHAPE{HEIGHT = 3.5}}
$!GLOBALCONTOUR 1  LEGEND{NUMBERTEXTSHAPE{HEIGHT = 4.5}}
$!REDRAWALL 
$!GLOBALCONTOUR 1  LEGEND{HEADERTEXTSHAPE{HEIGHT = 3.5}}
$!GLOBALCONTOUR 1  LEGEND{HEADERTEXTSHAPE{HEIGHT = 4.5}}
$!RENAMEDATASETVAR 
  VAR = 5
  NAME = 'p(x,y)' 
$!REDRAWALL 
$!PICK ADD
  X = 9.72534296029
  Y = 5.14348267715
#$!PICK SHIFT
#  X = 0.269566787004
#  Y = -0.504741338575
$!PICK ADD
  X = 9.49833935018
  Y = 5.24162682632
$!FRAMECONTROL POPATPOSITION
  X = 1.28364620939
  Y = 5.17152386263
$!PICK ADD
  X = 1.28364620939
  Y = 5.17152386263
$!THREEDVIEW 
  PSIANGLE = 53.0351
  THETAANGLE = 21.942
  ALPHAANGLE = 0
  VIEWERPOSITION
    {
    X = -4.32227953868
    Y = -11.470409345
    Z = 10123.0999938
    }
$!VIEW PUSH
$!VIEW FIT
$!FRAMECONTROL POPATPOSITION
  X = 4.92989169675
  Y = 3.19462028654
$!VIEW FIT
$!FRAMECONTROL POPATPOSITION
  X = 6.49054151625
  Y = 3.02637317368
$!VIEW FIT
$!RENAMEDATASETVAR 
  VAR = 1
  NAME = 'x' 
$!RENAMEDATASETVAR 
  VAR = 2
  NAME = 'y' 
$!RENAMEDATASETVAR 
  VAR = 2
  NAME = 'u(x,y)' 
$!RENAMEDATASETVAR 
  VAR = 4
  NAME = 'v(x,y)' 
$!RENAMEDATASETVAR 
  VAR = 3
  NAME = 'u(x,y)' 
$!RENAMEDATASETVAR 
  VAR = 3
  NAME = 'y' 
$!REDRAWALL 
$!REDRAWALL 
$!PICK SETMOUSEMODE
  MOUSEMODE = SELECT
$!FRAMECONTROL POPATPOSITION
  X = 6.03653429603
  Y = 5.84451231406
$!PICK ADD
  X = 6.03653429603
  Y = 5.84451231406
$!RENAMEDATASETVAR 
  VAR = 2
  NAME = 'y' 
$!RENAMEDATASETVAR 
  VAR = 3
  NAME = 'u(x,y)' 
$!REDRAWALL 
$!PICK ADD
  X = 5.63927797834
  Y = 4.87709141512

$!DRAWGRAPHICS TRUE     
$!REDRAWALL
