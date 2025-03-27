[ToDo]
 réparer aperture calculé
 ajouter caracteristiques capteur + crop facteur
 modifier diag du flash
 - pour une focale 50mm
 - Le premier chiffre est la vitesse du sujet en km/h.
 - Le deuxième est la distance de mise au point.
 - Le troisième est la vitesse d'obturation conseillée pour un sujet se déplaçant perpendiculairement à vous (sur une pendule vous êtes sur le 6 et votre sujet va du 9 au 3) 
 - Le quatrième est la vitesse d'obturation conseillée pour un sujet se déplaçant de biais (toujours sur le 6, le sujet va du 7.5 au 1.5)
 - Le cinquième est la vitesse d'obturation conseillée pour un sujet se déplaçant vers vous ou s'éloignant de vous. 
 8km/h (ex : marche à pied ) ---- 4M -- 1/500 - 1/250 - 1/125
 -------------------------------- 8M -- 1/250 - 1/125 - 1/60
 --------------------------------15M -- 1/125 - 1/60 - 1/30
 16km/h (ex : joggeur ) --------- 4M -- 1/1000 - 1/500 - 1/250
 -------------------------------- 8M -- 1/500 - 1/250 - 1/125
 --------------------------------15M -- 1/250 - 1/125 - 1/60
 40km/h (ex : un éléphant  )----- 4M -- 1/2000 - 1/1000 - 1/500
 -------------------------------- 8M -- 1/1000 - 1/500 - 1/250
 --------------------------------15M -- 1/500 - 1/250 - 1/125
 80km/h (ex : une libellule )---- 4M -- 1/4000 - 1/2000 - 1/1000
 -------------------------------- 8M -- 1/2000 - 1/1000 - 1/500
 --------------------------------15M -- 1/1000 - 1/500 - 1/250
 p(taille d'un photosite en mm) = (24x36)/21000000 = 0.0000411
 t(exposuretime) = sin(angle) x n(subjectdistance) x f(focale) x p(taille d'un photosite)/ v(vitesse du sujet en m/s)
 t = exposuretime
 angle = angle du déplacement du sujet (90° = perpendiculaire à la visée)
 n = subjectdistance en m
 f = focale en mm
 p = taille d'un photosite en mm
 v = distance du sujet en km/h
 t = sin(angle) * n * (35*35/f) * Coc / ( (v x 1000) / 3600 )
 FLASH:
 Power = sqr( aperture * subjectdistance / NGmax ) * (100/Iso)
 NGResult = NGmax * sqrt(Power)
 subjectdistanceMax = ( NGmax * sqrt(Iso/100) * sqrt(flashbias) ) / aperture
 aperture = ( NGmax * sqrt(Iso/100) * sqrt(flashbias) ) / subjectdistance
 1/180>cp1 ng36, 1/700>cp1/2 ng25, 1/1800>cp1/4 ng18, 1/2500>cp1/8 ng13, 1/3000>cp1/16 ng10, 1/3700>cp1/32 ng7
 430 ex
 1/32 = 1/4761 seconds
 1/16 = 1/3333 seconds
 1/8  = 1/1923 seconds
 1/4  = 1/900 seconds
 1/2  = 1/520 seconds
 1/1  = 1/520 seconds
 FlashDurationAtPower 0.03125 0.00021
 FlashDurationAtPower 0.0625 0.0003
 FlashDurationAtPower 0.125 0.0005
 FlashDurationAtPower 0.25 0.0011
 FlashDurationAtPower 0.5 0.01923
 FlashDurationAtPower 1.0 0.01923
 Flash prépondérant si deltaev flash >= 5, sinon, lumière ambiante prend le dessus, flash fill in
[Translate]   
 LANG                                = "English"                                                         "Francais"
 Set: DIAG.Settings                  = "%s - %s settings analys"                                         "Analyse du réglage du %s - %s"
 Set: DIAG.ExposureTime              = "ExposureTime set at %s"                                          "Vitesse réglé à %s"
 Set: DIAG.Aperture                  = "Aperture set at %s"                                              "Ouverture réglé à %s"
 Set: DIAG.DepthOfField              = "Sharpness: from %s to %s >> Depth of field %s"                   "Netteté: de %s à %s >> Profondeur de champ = %s"
 Set: DIAG.Hyperfocal                = "Hyperfocal: %s >> Sharpness from %s to infinite"                 "Hyperfocale: %s >> Netteté de %s à l'infini"
 Set: DIAG.Iso                       = "Iso set at %s"                                                   "Iso réglé à %s"
 Set: DIAG.Focale                    = "Focal set at %s (in 24x36 = %s)"                                 "Focale réglé à %s (en 24x36 = %s)"
 Set: DIAG.SubjectDistance           = "Subject distance = %s"                                           "Distance du sujet = %s"
 Set: DIAG.NoSubjectDistance         = "Subject distance not available"                                  "Distance du sujet non disponible"
 Set: DIAG.StillSubject              = "Still subject"                                                   "Sujet immobile"
 Set: DIAG.MoveSubject               = "Moving subject at focal %s"                                      "Sujets en mouvement pour une focale %s"
 Set: DIAG.UseTripod                 = "Tripod use recommended"                                          "Utilisation d'un trepied conseillé"
 Set: DIAG.NoTripodFlash             = "In all cases, Using a tripod not required because flash used"    "Dans tous les cas, l'utilisation d'un trepied n'est pas obligatoire grace au flash"
 Set: DIAG.Stab                      = "stabilized lens"                                                 "objectif stabilisé"
 Set: DIAG.NoStab                    = "non-stabilized lens"                                             "objectif non stabilisé"
 Set: DIAG.NoBlur                    = "%s is correct to avoid camera shake with a %s. (Limit: %s)"      "%s est correct pour eviter le flou de bouger avec un %s. (limite: %s)"
 Set: DIAG.Blur                      = "%s may produce blur with a %s. (Limit: %s)"                      "%s risque de produire un flou de bouger avec un %s. (Limite: %s)"
 Set: DIAG.Exposure                  = "Exposure analys"                                                 "Analyse de l'exposition"
 Set: DIAG.ExposureNaturalLight      = "%s measured. Light conditions equivalent %s."                    "%s mesuré. Condition d'éclairage équivalente %s."
 Set: DIAG.ExposureCalculated        = "%s estimaed. Light conditions equivalent %s."                    "%s estimé. Condition d'éclairage équivalente %s."
 Set: DIAG.ExposureOSettings         = "Photo seem to be %s with this settings (%s ,%s ,%s)"             "La photo semble %s avec ces réglages (%s, %s, %s)"
 Set: DIAG.ExposureOptimSpeed        = "ExposureTime at (%s, %s) = %s"                                   "Vitesse pour (%s, %s) = %s"
 Set: DIAG.ExposureOptimAperture     = "Aperture at (%s, %s) = %s"                                       "Ouverture pour (%s, %s) = %s"
 Set: DIAG.ExposureOptimIso          = "Iso at (%s, %s) = %s"                                            "Iso pour (%s, %s) = %s"
 Set: DIAG.OutOfCameraRange          = "%s is out of this camera range. Camera limit is: %s"             "Cet appareil n'est pas capable d'atteindre %s. Sa limite est: %s" 
 Set: DIAG.OutOfLensRange            = "%s is out of this lens range. Lens aperture limit is: %s"        "Cet objectif n'est pas capable d'atteindre %s. Sa limite est: %s" 
 Set: DIAG.Lens                      = "Lens: %s"                                                        "Objectif: %s"
 Set: DIAG.Focale24x36               = ", corresponding to focal %s"                                     ", correspondant à une focale %s"
 Set: DIAG.LensQuality               = "Quality indice (%s, %s) = %.1f/10"                               "Indice de qualité (%s, %s) = %.1f/10"
 Set: DIAG.LensQualityBestFocale     = "Best quality indice (%s, %s) = %.1f/10"                          "Indice de qualité maxi (%s, %s) =  %.1f/10"
 Set: DIAG.FlashExternal             = "External"                                                        "externe"
 Set: DIAG.FlashInternal             = "Built-in"                                                        "intégré"
 Set: DIAG.FlashFired                = "%sFlash fired"                                                   "Flash %sutilisé"
 Set: DIAG.FlashExposureBias         = "Flash exposure compens set at %s"                                "Correction d'exposition du flash de %s"
 Set: DIAG.FlashHightSync            = "Hight synchro used"                                              "Synchro haute vitesse utilisé"
 Set: DIAG.FlashNotUsed              = "Flash not used"                                                  "La photo a été prise sans flash"
 Set: DIAG.FlashDidNotFire           = "Flash did not fire"                                              "Le flash n'a pas fonctionné"
 Set: DIAG.FlashNoInfo               = "Flash information not available"                                 "Pas d'information disponible concernant le flash"
 Set: DIAG.FlashOk                   = "Correct flash range"                                             "Portée du flash suffisante"
 Set: DIAG.FlashLimit                = "Limit flash range (Max distance = %s)"                           "A la limite de la Portée du flash (portée maxi = %s)"
 Set: DIAG.FlashOutOfRange           = "Out of flash range (Max distance = %s)"                          "La portée du flash n'est pas suffisante (Portée maxi = %s)"
 Set: DIAG.FlashRangeMax             = "Max flash range = %s"                                            "Portée maxi du flash = %s"
 Set: DIAG.FlashExposureTime         = "ExposureTime to consider = %s (flash duration)"                  "Vitesse à considérer = %s (durée de l'éclair du flash)"
 Set: DIAG.FlashDuration             = "Flash duration = %s"                                             "Durée de l'éclair du flash = %s"
 Set: DIAG.FlashFillIn               = "Flash used for fill-in"                                          "Flash utilisé pour déboucher les ombres"
 Set: DIAG.FlashPowerUsed            = "%.0f%% power flash max used"                                     "Flash utilisé a %.0f%% de sa puissance maxi"
 Set: DIAG.FlashNGNGLimit            = "Calculate NG: %.0f, Needed NG: %.0f"                             "NG calculé: %.0f, NG mini nécessaire: %.0f"
 Set: DIAG.FlashNG                   = "Calculate NG: %.0f"                                              "NG calculé: %.0f"
 Set: INTF.LabelFileConfig           = "File config"                                                     "Fichier de configuration"
 Set: INTF.LabelDefaultSearchPath    = "Default search path"                                             "Chemin de recherche par defaut"
 Set: INTF.ButtonBrowse              = "Browse"                                                          "Parcourir"
 Set: INTF.TabItemViewer             = "Viewer"                                                          "Visualiseur"
 Set: INTF.TabItemExifData           = "Exif data"                                                       "Données Exif"
 Set: INTF.TabItemConfig             = "Settings"                                                        "Configuration"
 Set: INTF.RadioButtonUserList       = "User list"                                                       "Liste utilisateur"
 Set: INTF.RadioButtonFullList       = "Full list"                                                       "Liste complète"
 Set: INTF.RadioButtonFullListExpert = "Full list (Expert)"                                              "Liste complète (Expert)"
 Set: INTF.CameraModel               = "Camera model"                                                    "Appareil photo"
 Set: INTF.Lens                      = "Lens"                                                            "Objectif"
 Set: INTF.TiffData                  = "TIFF DATA for"                                                   "Données TIFF pour"
 Set: INTF.Loading                   = "Loading...."                                                     "Chargement...."
 Set: INTF.PhotoInfo                 = "Photo taken with a %s - %s at %s"                                "Photo prise avec un %s - %s le %s"
 Set: Hyper.HyperDistance            = "Hyperfocal Distance"                                             "Distance Hyperfocale"
 Set: FocusDist.FromTo               = "Dof:  From  %s  to  %s  -->  %s"                                 "Pdc:  de  %s  à  %s  -->  %s"
 Set: FocusDist.FromToInf            = "Dof:  From  %s  to  Inf"                                         "Pdc:  de  %s  à  Inf"
 Set: SubjectDist.SubjectDist        = "Subject Distance"                                                "Distance du sujet"
 Set: NaturalLight.Idx0              = "to black Night (0-3 EV)"                                         "à une nuit avec ciel couvert (0-3 IL)"
 Set: NaturalLight.Idx1              = "to night, starlight only (3-4.5 EV)"                             "à une nuit claire sans lune (3-4.5 IL)"
 Set: NaturalLight.Idx2              = "to half moon (4.5-5.5 EV)"                                       "à une nuit en demi lune (4.5-5.5 IL)"
 Set: NaturalLight.Idx3              = "to full moon (5.5-6.5 EV)"                                       "à une nuit en pleine lune (5.5-6.5 IL)"
 Set: NaturalLight.Idx4              = "to down end, start dusk (6.5-8.5 EV)"                            "à la fin de l'aube, ou crépuscule (6.5-8.5 IL)"
 Set: NaturalLight.Idx5              = "to down; dusk (8.5-9.5 EV)"                                      "à l'aube ou au crépuscule (8.5-9.5 IL)"
 Set: NaturalLight.Idx6              = "to morning, begining of evening with clouds (9.5-11.5 EV)"       "au matin ou début de soirée, ciel couvert (9.5-11.5 IL)"
 Set: NaturalLight.Idx7              = "to day with clouds (11.5-12 EV)"                                 "à une journée ciel couvert (11.5-12 IL)"
 Set: NaturalLight.Idx8              = "to sunny day in the shade (12-13 EV)"                            "à une journée ensoleillée à l'ombre (12-13 IL)"
 Set: NaturalLight.Idx9              = "to hazy sun (13-14 EV)"                                          "à un soleil brumeux (13-14 IL)"
 Set: NaturalLight.Idx10             = "to direct sun (14-15 EV)"                                        "à un soleil direct (14-15 IL)"
 Set: NaturalLight.Idx11             = "to direct sun on snow or sand (15-16 EV)"                        "à un soleil direct sur neige ou sable (15-16 IL)"
 Set: NaturalLight.Idx12             = "to Sun face (16+ EV)"                                            "à un soleil de face (16+ IL)"
 Set: NaturalLight.Idx13             = "No exposure data available"                                      "Pas de mesure d'exposition disponible"
 Set: Exposure.EV                    = "EV"                                                              "IL"
 Set: Exposure.Idx0                  = "correctly exposed"                                               "correctement exposée"
 Set: Exposure.Idx1                  = "slightly underexposed"                                           "légèrement sous-exposée"
 Set: Exposure.Idx2                  = "underexposed"                                                    "sous exposée"
 Set: Exposure.Idx3                  = "severely underexposed"                                           "fortement sous-exposée"
 Set: Exposure.Idx4                  = "lightly overexposed"                                             "légèrement sur-exposée"
 Set: Exposure.Idx5                  = "overexposed"                                                     "sur exposée"
 Set: Exposure.Idx6                  = "strongly overexposed"                                            "fortement sur-exposée"
 Set: Exposure.Idx7                  = "correctly compensated by flash"                                  "correctement compensé par le flash"
 Set: Exposure.Idx8                  = "underexposed. Subject too far from flash"                        "sous-exposée. Le sujet est trop loin du flash"
 Set: Exposure.Idx9                  = "correct, flash fill in"                                          "correcte, ombres débouchées au flash"
 Set: Exposure.Idx10                 = "correct. Subject too far from flash"                             "correcte. Le sujet est trop loin du flash"
 Set: Exposure.Idx11                 = "overexposed, flash fill in"                                      "sur-exposée, ombres débouchées au flash"
 Set: Exposure.Idx12                 = "overexposed and subject too far from flash"                      "sur-exposée et le sujet est trop loin du flash"
 Set: Exposure.Idx13                 = "No exposure data available"                                      "Pas de mesure d'exposition disponible"
[EnumArrays]
 AESetting = {
  0xffff=Unknown;
  0=Normal AE;
  1=Exposure Compensation;
  2=AE Lock;
  3=AE Lock + Exposure Compensation;
  4=No AE
  }
 AFPoint = {
  0x0000=Unknown;
  0x2005=Manual AF point selection;
  0x3000=None (MF);
  0x3001=Auto AF point selection;
  0x3002=Right;
  0x3003=Center;
  0x3004=Left;
  0x4001=Auto AF point selection;
  0x4006=Face Detect
  }
 AFPointsInFocus.BitEnum = {
  ******************1=pt1;
  *****************1*=pt2;
  ****************1**=pt3;
  ***************1***=pt4;
  **************1****=pt5;
  *************1*****=pt6;
  ************1******=pt7;
  ***********1*******=pt8;
  **********1********=pt9;
  *********1*********=pt10;
  ********1**********=pt11;
  *******1***********=pt12;
  ******1************=pt13;
  *****1*************=pt14;
  ****1**************=pt15;
  ***1***************=pt16;
  **1****************=pt17;
  *1*****************=pt18;
  1******************=pt19
  }
 AutoExposureBracketing = {
  -1=On;
  0=Off;
  1=On (shot 1);
  2=On (shot 2);
  3=On (shot 3)
  }
 BlackAndWhiteMode = {
  0=Off;
  1=On
  }
 AutoISO = {
  0=Off;
  1=On
  }
 BracketMode = {
  0=Off;
  1=AEB;
  2=FEB;
  3=ISO;
  4=WB
  }
 CameraType = {
  248=EOS High-end;
  250=Compact;
  252=EOS Mid-range;
  255=DV Camera
  }
 ColorSpace = {
  0x0001=sRGB;
  0xffff=Uncalibred
  }
 ColorTone = {
  0=Normal
  }
 ComponentConfiguration = {
  0x030201=Other than YCbCr;
  0x060504=YCbCr RGB Uncompressed
  }
 Compression = {
  0x0001=Uncompressed;
  0x0002=CCITT 1D;
  0x0003=T4/Group 3 Fax;
  0x0004=T6/Group 4 Fax;
  0x0005=LZW;
  0x0006=JPEG (old-style);
  0x0007=JPEG;
  0x0008=Adobe Deflate;
  0x0009=JBIG B&W;
  0x000a=JBIG Color;
  0x0063=JPEG;
  0x0106=Kodak 262;
  0x7ffe=Next;
  0x7fff=Sony ARW Compressed;
  0x8001=Packed RAW;
  0x8002=Samsung SRW Compressed;
  0x8003=CCIRLEW;
  0x8005=PackBits;
  0x8029=Thunderscan;
  0x8063=Kodak KDC Compressed;
  0x807f=IT8CTPAD;
  0x8080=IT8LW;
  0x8081=IT8MP;
  0x8082=IT8BL;
  0x808c=PixarFilm;
  0x808d=PixarLog;
  0x80b2=Deflate;
  0x80b3=DCS;
  0x8765=JBIG;
  0x8774=SGILog;
  0x8775=SGILog24;
  0x8798=JPEG 2000;
  0x8799=Nikon NEF Compressed;
  0x879b=JBIG2 TIFF FX;
  0x879e=Microsoft Document Imaging (MDI) Binary Level Codec;
  0x879f=Microsoft Document Imaging (MDI) Progressive Transform Codec;
  0x87a0=Microsoft Document Imaging (MDI) Vector;
  0xfde8=Kodak DCR Compressed;
  0xffff=Pentax PEF Compressed
  }
 ContinuousDrive = {
  0xffff=Unknown;
  0x0000=Single;
  0x0001=Continuous;
  0x0002=Movie;
  0x0003=Continuous, Speed Priority;
  0x0004=Continuous, Low;
  0x0005=Continuous, High;
  0x0006=Silent Single;
  0x0008=Manual
  }
 Contrast = {
  0=Normal
  }
 CustomRendered = {
  0=Normal process;
  1=Custom process
  }
 DigitalZoom = {
  0=No digital zoom;
  1=x2;
  2=x4;
  3=Other
  }
 EasyMode = {
  0=Full auto;
  1=Manual;
  2=Landscape;
  3=Fast shutter;
  4=Slow shutter;
  5=Night;
  6=Gray Scale;
  7=Sepia;
  8=Portrait;
  9=Sports;
  10=Macro;
  11=Black & White;
  12=Pan focus;
  13=Vivid;
  14=Neutral;
  15=Flash Off;
  16=Long Shutter;
  17=Super Macro;
  18=Foliage;
  19=Indoor;
  20=Fireworks;
  21=Beach;
  22=Underwater;
  23=Snow;
  24=Kids & Pets;
  25=Night Snapshot;
  26=Digital Macro;
  27=My Colors;
  28=Movie Snap;
  29=Super Macro 2;
  30=Color Accent;
  31=Color Swap;
  32=Aquarium;
  33=ISO 3200;
  34=ISO 6400;
  35=Creative Light Effect;
  36=Easy;
  37=Quick Shot;
  38=Creative Auto;
  39=Zoom Blur;
  40=Low Light;
  41=Nostalgic;
  42=Super Vivid;
  43=Poster Effect;
  44=Face Self-timer;
  45=Smile;
  46=Wink Self-timer;
  47=Fisheye Effect;
  48=Miniature Effect;
  49=High-speed Burst;
  50=Best Image Selection;
  51=High Dynamic Range;
  52=Handheld Night Scene;
  59=Scene Intelligent Auto;
  257=Spotlight;
  258=Night 2;
  259=Night+;
  260=Super Night;
  261=Sunset;
  263=Night Scene;
  264=Surface;
  265=Low Light 2
  }
 ExposureCompensation = {
  0xffc0=-2 EV;
  0xffcc=-1.67 EV;
  0xffd0=-1.5 EV;
  0xffd4=-1.33 EV;
  0xffe0=-1 EV;
  0xffec=-0.67 EV;
  0xfff0=-0.5 EV;
  0xfff4=-0.33 EV;
  0x0000=0 EV;
  0x000c=0.33 EV;
  0x0010=0.5 EV;
  0x0014=0.67 EV;
  0x0020=1 EV;
  0x002c=1.33 EV;
  0x0030=1.5 EV;
  0x0034=1.67 EV;
  0x0040=2 EV
  }
 ExposureMode = {
  0=Auto exposure;
  1=Manual exposure;
  2=Auto bracket
  }
 ExposureProgram = {
  0=n/a;
  1=M;
  2=Auto;
  3=AV;
  4=TV;
  5=CA;
  6=Sport;
  7=Face;
  8=Land
  }
 Canon.MakerNote.ExposureProgram = {
  0=Auto;
  1=P;
  2=TV;
  3=AV;
  4=M;
  5=CA;
  6=MDep;
  7=Bulb
  }
 FileSource = {
  1=Film Scanner; 
  2=Reflection Print Scanner; 
  3=Digital Still Camera
  }
 FilterEffect = {
  0xffff=Unknown;
  0=None;
  1=Yellow;
  2=Orange;
  3=Red;
  4=Green
  }
 Exif.Flash.BitEnum = {
  *******0=Flash did not fire;
  *******1=Flash fired;
  *****10*=Return light not detected;
  *****11*=Return light detected;
  ***01***=Compulsory flash firing;
  ***10***=No Compulsory flash;
  ***11***=Auto mode;
  **1*****=No flash function;
  *1******=Red-eye reduction
  }
 FlashActivity = {
  0=Flash Did Not Fire;
  1=Flash Fired
  }
 FlashBias = {
  0xFFC0=-2 EV;
  0xFFCC=-1.67 EV;
  0xFFD0=-1.5 EV;
  0xFFD4=-1.33 EV;
  0xFFE0=-1 EV;
  0xFFEC=-0.67 EV;
  0xFFF0=-0.5 EV;
  0xFFF4=-0.33 EV;
  0x0000=0 EV;
  0x000C=0.33 EV;
  0x0010=0.5 EV;
  0x0014=0.67 EV;
  0x0020=1 EV;
  0x002C=1.33 EV;
  0x0030=1.5 EV;
  0x0034=1.67 EV;
  0x0040=2 EV
  }
 Canon.FlashBits.BitEnum = {
  ***************1=Manual;
  **************1*=TTL;
  *************1**=A-TTL;
  ************1***=E-TTL;
  ***********1****=Hight synchro;
  ********1*******=2nd-curtain sync used;
  ****1***********=FP sync used;
  **1*************=BuiltIn;
  *1**************=External
  }
 Canon.FlashMeteringMode = {
  0=E-TTL;
  3=TTL;
  4=External Auto;
  5=External Manual;
  6=Off
  }
 Canon.FlashMode = {
  0=Flash not fired;
  1=Auto;
  2=On;
  3=Red-eye reduction;
  4=Slow-sync;
  5=Red-eye reduction (Auto);
  6=Red-eye reduction (On);
  16=External
  }
 FlashPixVersion = {
  0x30303130=0100 FPXR
  }
 FocalPlaneResolutionUnit = {
  0=Unknown;
  1=Inches;
  2=Centimeters;
  3=Pixel
  }
 FocalType = {
  0=Unknown;
  1=Fixed;
  2=Zoom
  }
 FocalUnits = {
  1=mm
  }
 FocusAreaMode = {
  0=Manual;
  2=Single;
  4=Multi;
  5=Face;
  7=Zone;
  8=Points;
  9=Spot     
  }
 FocusMode = {
  0=OneShot;
  1=AIServo;
  2=AIFocus;
  3=Manual;
  4=Single;
  5=Cont;
  6=Manual;
  16=Pan
  }
 FocusRange = {
  0=Manual;
  1=Auto;
  2=Unknown;
  3=Macro;
  4=Very Close;
  5=Close;
  6=Middle Range;
  7=Far Range;
  8=Pan Focus;
  9=Super Macro;
  10=Infinity
  }
 Canon.HighlightTonePriority = {
  0 =Off; 
  1 =On 
  }
 Canon.ImageSize = {
  0xffff=Unknown;
  0=Large;
  1=Medium;
  2=Small;
  5=Medium 1;
  6=Medium 2;
  7=Medium 3;
  8=Postcard;
  9=Widescreen;
  10=Medium Widescreen;
  14=Small 1;
  15=Small 2;
  16=Small 3;
  128=640x480 Movie;
  129=Medium Movie;
  130=Small Movie;
  137=1280x720 Movie;
  142=1920x1080 Movie
  }
 ImageStabilization = {
  0xffff=Unknown;
  0=Off;
  1=On;
  2=On, Shot Only;
  3=On, Panning;
  4=On, Video
  }
 ISOSpeed = {
  0x7fff=Unknown;
  0=See EXIF Tag;
  15=Auto ISO;
  16=ISO 50;
  17=ISO 100;
  18=ISO 200;
  19=ISO 400
  }
 JpegQuality = {
  1=Standard Quality;
  2=High Quality;
  3=Super High Quality;
  33=Not compressed;
  34=Not compressed/HyPict interpolated
  }
 LensType  = {
  29=Canon EF 50mm f/1.8 II;
  45=Canon EF-S 18-55mm f/3.5-5.6;
  48=Canon EF-S 18-55mm f/3.5-5.6 IS;
  49=Canon EF-S 55-250mm f/4-5.6 IS;
  209=Canon EF 55-200mm f/4.5-5.6;
  237=Canon EF 24-105mm f/4L IS;
  235=Canon EF-S 10-22mm f/3.5-4.5 USM
  }
 LightSource = {
  0=Unknown;
  1=Daylight;
  2=Fluorescent;
  3=Tungsten (incandescent light);
  4=Flash;9=Fine weather;
  10=Cloudy weather;
  11=Shade;
  12=Daylight fluorescent (D 5700 - 7100K);
  13=Day white fluorescent (N 4600 - 5400K);
  14=Cool white fluorescent (W 3900 - 4500K);
  15=White fluorescent (WW 3200 - 3700K);
  17=Standard light A;
  18=Standard light B;
  19=Standard light C;
  20=D55;
  21=D65;
  22=D75;
  23=D50;
  24=ISO studio tungsten;
  255=Other light source
  }
 MacroMode = {
  0=Off;
  1=On;
  2=Normal
  }
 ManualFlashOutput = {
  0x0000=Unknown;
  0x0500=Full;
  0x0502=Medium;
  0x0504=Low;
  0x7fff=Unknown
  }
 Exif.MeteringMode = {
  0=unknown;
  1=Average;
  2=Center Weighted Average;
  3=Spot;
  4=Multi Spot;
  5=Pattern;
  6=Partial;
  255=other
  }
 Canon.MakerNote.MeteringMode = {
  0=Default;
  1=Spot;
  2=Average;
  3=Evaluative;
  4=Partial;
  5=Center Average
  }
 NDFilter = {
  0xffff=Unknown;
  0=Off;
  1=On
  }
 NoiseReduction = {
  0=Off',
  1=On (mode 1);
  2=On (mode 2);
  3=On (mode 3);
  4=On (mode 4)
  }
 PanoramaDirection = {
  1=Left-Right;
  2=Right-Left;
  3=Bottom-Top;
  4=Top-Bottom
  }
 PhotoEffect = {
  0xffff=Unknown;
  0=Off;
  1=Vivid;
  2=Neutral;
  3=Smooth;
  4=Sepia;
  5=B&W;
  6=Custom;
  100=My Color Data
  }
 Quality = {
  0x0001=Economy;
  0x0002=Normal;
  0x0003=Fine;
  0x0004=RAW;
  0x0005=Superfine;
  0x0082=Normal Movie
  }
 RecordMode = {
  1=JPEG;
  2=CRW+THM;
  3=AVI+THM;
  4=TIFF;
  5=TIFF+JPEG;
  6=CR2;
  7=CR2+JPEG;
  9=Video
  }
 ResolutionUnit = {
  0=Unknown;
  1=Inches;
  2=Centimeters
  }
 Rotate = {
  0=Not definied;
  1=Horizontal;
  2=Flip horizontal;
  3=Rotate 180;
  4=Flip vertical;
  5=Transpose;
  6=rotate 90;
  7=Transverse;
  8=Rotate 270
  }
 Saturation = {
  0=Normal
  }
 SceneCaptureType = {
  0=Standard;
  1=Landscape;
  2=Portrait;
  3=Night scene
  }
 SceneType = {
  0=Standard;
  1=Landscape;
  2=Portrait;
  3=Night scene
  }
 Sensing = {
  1=Unknown;
  2=One-chip color area sensor;
  3=Two-chip color area sensor;
  4=Three-chip color area sensor;
  5=Color sequential area sensor;
  7=Trilinear sensor;
  8=Color sequential linear sensor
  }
 Sharpness = {
  0x7fff=Unknown;
  0x0000=Unknown; 
  0x0001=Lowest; 
  0x0002=Low;
  0x0003=Standard; 
  0x0004=High;
  0x0005=Highest
  }
 SharpnessFrequency = {
  0x7fff=Unknown;
  0x0000=Normal;
  0x0001=Soft;
  0x0002=Hard
  }
 ShootingMode = {
  0=Normal;
  2=Fast;
  3=Panorama
  }
 SlowShutter = {
  0=Off;
  1=Night Scene;
  2=On;
  3=None
  }
 SpotMeteringMode = {
  0xffff=Unknown;
  0=Center;
  1=AF Point
  }
 SRAWQuality = {
  0xffff=Unknown;
  0=Unknown;
  1=sRAW1 (mRAW);
  2=sRAW2 (sRAW)
  }
 SubjectDistanceType = {
  0=Unknown;
  1=Macro;
  2=Close view;
  3=Distant view
  }
 ToneCurve = {
  0=Standard;
  1=Manual;
  2=Custom
  }
 ToningEffect = {
  0xffff=Unknown;
  0=None;
  1=Sepia;
  2=Blue;
  3=Purple;
  4=Green
  }
 WhiteBalance = {
  0xffff=Unknown;
  0x0000=Auto white balance;
  0x0001=Manual white balance
  }
 YCBCRPositioning = {
  0=Unknown;
  1=Center of pixel array;
  2=Datum point
  }
 Canon.Canon EOS 7D.YCBCRPositioning = {
  1=Centered;
  2=Co-sited
  }
[Models MapData]
 Models: Count= 6
  Model: Caption= "Default" "Default"
   SetBitTag: Flash.Fired Exif Flash=*******1
   MapIfds: Count= 3
    MapIfd: Caption= "Ifd0"
     MapSubIfds: Count= 1
      MapSubIfd: Caption= "Exif" TagNumber= 0X8769 IsPointer= 1 Seek= 0
     MapDatas:
      MapData: TagNumber= 0X0100 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageWidth"
      MapData: TagNumber= 0X0101 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageHeight"
      Group: "BitSampleRGB" TagNumber= 0X0102
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleR"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleG"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleB"
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Compression"
      MapData: TagNumber= 0X010E Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageDesc"
      MapData: TagNumber= 0X010F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Maker"
      MapData: TagNumber= 0X0110 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0111 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewOffset"
      MapData: TagNumber= 0X0112 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Rotate"
      MapData: TagNumber= 0X0117 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewLength"
      MapData: TagNumber= 0X011A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "XResolution"
      MapData: TagNumber= 0X011B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YResolution"
      MapData: TagNumber= 0X0128 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ResolutionUnit"
      MapData: TagNumber= 0X0131 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Software"
      MapData: TagNumber= 0X0132 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X013B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Artist"
      MapData: TagNumber= 0X0213 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YCBCRPositioning"
      MapData: TagNumber= 0X8298 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Copyright"
      MapData: TagNumber= 0X8769 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 0 Format= 0 Caption= "Exif"
      MapData: TagNumber= 0X8825 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "GpsInfo"
      MapData: TagNumber= 0XA401 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "CustomRendered"
      MapData: TagNumber= 0XA402 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureMode"
      MapData: TagNumber= 0XA403 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
      MapData: TagNumber= 0XA404 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoomRatio"
      MapData: TagNumber= 0XA405 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalLengthIn35mmFilm"
      MapData: TagNumber= 0XA406 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneCaptureType"
      MapData: TagNumber= 0XA407 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "GainControl"
      MapData: TagNumber= 0XA408 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
      MapData: TagNumber= 0XA409 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
      MapData: TagNumber= 0XA40A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
      MapData: TagNumber= 0XC4A5 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Sony0xC4A5"
    MapIfd: Caption= "Ifd1"
     MapSubIfds: Count= 0
     MapDatas:
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Compression"
      MapData: TagNumber= 0X010F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Maker"
      MapData: TagNumber= 0X0110 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0112 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Rotate"
      MapData: TagNumber= 0X011A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "XResolution"
      MapData: TagNumber= 0X011B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YResolution"
      MapData: TagNumber= 0X0128 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ResolutionUnit"
      MapData: TagNumber= 0X0132 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X0201 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ThumbOffset"
      MapData: TagNumber= 0X0202 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ThumbLength"
      MapData: TagNumber= 0X0213 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YCBCRPositioning"
    MapIfd: Caption= "Exif"
     MapSubIfds: Count= 0
     MapDatas:
      MapData: TagNumber= 0X829D Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 2 Caption= "Aperture"
      MapData: TagNumber= 0X829A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 3 Caption= "ExposureTime"
      MapData: TagNumber= 0X8822 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ExposureProgram"
      MapData: TagNumber= 0X8827 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 4 Caption= "Iso"
      MapData: TagNumber= 0X9000 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ExifVersion"
      MapData: TagNumber= 0X9003 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X9004 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DataTimeDigitized"
      MapData: TagNumber= 0X9101 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ComponentConfiguration"
      MapData: TagNumber= 0X9102 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CompressedBitsPerPixel"
      MapData: TagNumber= 0X9201 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 3 Formula= "ExposureTimeApex"          = "1/2^Value"
      MapData: TagNumber= 0X9202 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "APertureApex"              = "e^((Value*ln(2))/2)"
      MapData: TagNumber= 0X9203 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureValueApex"
      MapData: TagNumber= 0X9204 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureBiasApex"
      MapData: TagNumber= 0X9205 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Caption= "MaxApertureValue"
      MapData: TagNumber= 0X9206 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 6 Caption= "SubjectDistance"
      MapData: TagNumber= 0X9207 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "MeteringMode"
      MapData: TagNumber= 0X9208 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LightSource"
      MapData: TagNumber= 0X9209 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Flash"
      MapData: TagNumber= 0X920A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 5 Caption= "Focale"
      MapData: TagNumber= 0X927C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 0 Format= 0 Caption= "MakerNote"
      MapData: TagNumber= 0X9286 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "UserComment"
      MapData: TagNumber= 0X9290 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTime"
      MapData: TagNumber= 0X9291 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTimeOriginal"
      MapData: TagNumber= 0X9292 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTimeDigitized"
      MapData: TagNumber= 0XA000 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashPixVersion"
      MapData: TagNumber= 0XA001 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ColorSpace"
      MapData: TagNumber= 0XA002 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "PixelXDimension"
      MapData: TagNumber= 0XA003 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "PixelYDimension"
      MapData: TagNumber= 0XA004 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "RelatedSoundFile"
      MapData: TagNumber= 0XA005 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "InteroperabilityIfd"
      MapData: TagNumber= 0XA20E Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneXResolution"
      MapData: TagNumber= 0XA20F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneYResolution"
      MapData: TagNumber= 0XA210 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneResolutionUnit"
      MapData: TagNumber= 0XA217 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sensing"
      MapData: TagNumber= 0XA300 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FileSource"
      MapData: TagNumber= 0XA301 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneType"
      MapData: TagNumber= 0XA401 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CustomRendered"
      MapData: TagNumber= 0XA402 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureMode"
      MapData: TagNumber= 0XA403 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
      MapData: TagNumber= 0XA404 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoomRatio"
      MapData: TagNumber= 0XA405 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "FocalLengthIn35mmFilm"
      MapData: TagNumber= 0XA406 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneCaptureType"
      MapData: TagNumber= 0XA407 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "GainControl"
      MapData: TagNumber= 0XA408 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
      MapData: TagNumber= 0XA409 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
      MapData: TagNumber= 0XA40A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
      MapData: TagNumber= 0XA40C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SubjectDistanceType"
  Model: Caption= "FUJIFILM" "FinePix S5000"
   Set: FlashFillInLight= -3.5
   Set: Sensor=3.96 5.27 "1/2.7" 3100000
   Set: ExposureTimeRange=0.0005 2.0
   Set: IsoRange=160.0 800.0
   Set: LensBuiltIn=Yes
   SetBitTag: Flash.Fired Exif Flash=*******1
   MapIfds: Count= 3
    MapIfd: Caption= "Ifd0"
     MapSubIfds: Count= 1
      MapSubIfd: Caption= "Exif" TagNumber= 0X8769 IsPointer= 1 Seek= 0
     MapDatas:
      MapData: TagNumber= 0X0100 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageWidth"
      MapData: TagNumber= 0X0101 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageHeight"
      Group: "BitSampleRGB" TagNumber= 0X0102
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleR"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleG"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleB"
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Compression"
      MapData: TagNumber= 0X010E Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageDesc"
      MapData: TagNumber= 0X010F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Maker"
      MapData: TagNumber= 0X0110 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0111 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewOffset"
      MapData: TagNumber= 0X0112 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Rotate"
      MapData: TagNumber= 0X0117 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewLength"
      MapData: TagNumber= 0X011A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "XResolution"
      MapData: TagNumber= 0X011B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YResolution"
      MapData: TagNumber= 0X0128 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ResolutionUnit"
      MapData: TagNumber= 0X0131 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Software"
      MapData: TagNumber= 0X0132 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X013B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Artist"
      MapData: TagNumber= 0X0213 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YCBCRPositioning"
      MapData: TagNumber= 0X8298 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Copyright"
      MapData: TagNumber= 0X8769 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 0 Format= 0 Caption= "Exif"
      MapData: TagNumber= 0X8825 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "GpsInfo"
      MapData: TagNumber= 0XA401 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "CustomRendered"
      MapData: TagNumber= 0XA402 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureMode"
      MapData: TagNumber= 0XA403 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
      MapData: TagNumber= 0XA404 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoomRatio"
      MapData: TagNumber= 0XA405 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalLengthIn35mmFilm"
      MapData: TagNumber= 0XA406 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneCaptureType"
      MapData: TagNumber= 0XA407 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "GainControl"
      MapData: TagNumber= 0XA408 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
      MapData: TagNumber= 0XA409 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
      MapData: TagNumber= 0XA40A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
      MapData: TagNumber= 0XC4A5 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Sony0xC4A5"
    MapIfd: Caption= "Ifd1"
     MapSubIfds: Count= 0
     MapDatas:
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Compression"
      MapData: TagNumber= 0X010F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Maker"
      MapData: TagNumber= 0X0110 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0112 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Rotate"
      MapData: TagNumber= 0X011A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "XResolution"
      MapData: TagNumber= 0X011B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YResolution"
      MapData: TagNumber= 0X0128 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ResolutionUnit"
      MapData: TagNumber= 0X0132 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X0201 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ThumbOffset"
      MapData: TagNumber= 0X0202 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ThumbLength"
      MapData: TagNumber= 0X0213 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YCBCRPositioning"
    MapIfd: Caption= "Exif"
     MapSubIfds: Count= 0
     MapDatas:
      MapData: TagNumber= 0X829D Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 2 Caption= "Aperture"
      MapData: TagNumber= 0X829A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 3 Caption= "ExposureTime"
      MapData: TagNumber= 0X8822 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ExposureProgram"
      MapData: TagNumber= 0X8827 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 4 Caption= "Iso"
      MapData: TagNumber= 0X9000 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ExifVersion"
      MapData: TagNumber= 0X9003 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X9004 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DataTimeDigitized"
      MapData: TagNumber= 0X9101 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ComponentConfiguration"
      MapData: TagNumber= 0X9102 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CompressedBitsPerPixel"
      MapData: TagNumber= 0X9201 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 3 Formula= "ExposureTimeApex"          = "1/2^Value"
      MapData: TagNumber= 0X9202 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "APertureApex"              = "e^((Value*ln(2))/2)"
      MapData: TagNumber= 0X9203 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureValueApex"
      MapData: TagNumber= 0X9204 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureBiasApex"
      MapData: TagNumber= 0X9205 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Caption= "MaxApertureValue"
      MapData: TagNumber= 0X9206 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 6 Caption= "SubjectDistance"
      MapData: TagNumber= 0X9207 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "MeteringMode"
      MapData: TagNumber= 0X9208 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LightSource"
      MapData: TagNumber= 0X9209 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Flash"
      MapData: TagNumber= 0X920A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 5 Caption= "Focale"
      MapData: TagNumber= 0X927C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 0 Format= 0 Caption= "MakerNote"
      MapData: TagNumber= 0X9286 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "UserComment"
      MapData: TagNumber= 0X9290 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTime"
      MapData: TagNumber= 0X9291 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTimeOriginal"
      MapData: TagNumber= 0X9292 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTimeDigitized"
      MapData: TagNumber= 0XA000 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashPixVersion"
      MapData: TagNumber= 0XA001 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ColorSpace"
      MapData: TagNumber= 0XA002 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "PixelXDimension"
      MapData: TagNumber= 0XA003 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "PixelYDimension"
      MapData: TagNumber= 0XA004 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "RelatedSoundFile"
      MapData: TagNumber= 0XA005 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "InteroperabilityIfd"
      MapData: TagNumber= 0XA20E Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneXResolution"
      MapData: TagNumber= 0XA20F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneYResolution"
      MapData: TagNumber= 0XA210 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneResolutionUnit"
      MapData: TagNumber= 0XA217 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sensing"
      MapData: TagNumber= 0XA300 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FileSource"
      MapData: TagNumber= 0XA301 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneType"
      MapData: TagNumber= 0XA401 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CustomRendered"
      MapData: TagNumber= 0XA402 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureMode"
      MapData: TagNumber= 0XA403 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
      MapData: TagNumber= 0XA404 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoomRatio"
      MapData: TagNumber= 0XA405 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "FocalLengthIn35mmFilm"
      MapData: TagNumber= 0XA406 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneCaptureType"
      MapData: TagNumber= 0XA407 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "GainControl"
      MapData: TagNumber= 0XA408 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
      MapData: TagNumber= 0XA409 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
      MapData: TagNumber= 0XA40A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
      MapData: TagNumber= 0XA40C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SubjectDistanceType"
  Model: Caption= "SEIKO EPSON CORP" "PhotoPC 800"
   Set: FlashFillInLight= -3.5
   Set: Sensor=4.8 6.4 "1/2" 2140000
   Set: ExposureTimeRange=0.00133 0.5
   Set: IsoRange=100.0 400.0
   Set: LensBuiltIn=Yes
   SetBitTag: Flash.Fired Exif Flash=*******1
   MapIfds: Count= 4
    MapIfd: Caption= "Ifd0"
     MapSubIfds: Count= 1
      MapSubIfd: Caption= "Exif" TagNumber= 0X8769 IsPointer= 1 Seek= 0
     MapDatas:
      MapData: TagNumber= 0X0100 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageWidth"
      MapData: TagNumber= 0X0101 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageHeight"
      Group: "BitSampleRGB" TagNumber= 0X0102
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleR"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleG"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleB"
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Compression"
      MapData: TagNumber= 0X010E Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageDesc"
      MapData: TagNumber= 0X010F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Maker"
      MapData: TagNumber= 0X0110 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0111 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewOffset"
      MapData: TagNumber= 0X0112 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Rotate"
      MapData: TagNumber= 0X0117 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewLength"
      MapData: TagNumber= 0X011A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "XResolution"
      MapData: TagNumber= 0X011B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YResolution"
      MapData: TagNumber= 0X0128 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ResolutionUnit"
      MapData: TagNumber= 0X0131 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Software"
      MapData: TagNumber= 0X0132 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X013B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Artist"
      MapData: TagNumber= 0X0213 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YCBCRPositioning"
      MapData: TagNumber= 0X8298 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Copyright"
      MapData: TagNumber= 0X8769 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 0 Format= 0 Caption= "Exif"
      MapData: TagNumber= 0X8825 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "GpsInfo"
      MapData: TagNumber= 0XA401 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "CustomRendered"
      MapData: TagNumber= 0XA402 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureMode"
      MapData: TagNumber= 0XA403 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
      MapData: TagNumber= 0XA404 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoomRatio"
      MapData: TagNumber= 0XA405 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalLengthIn35mmFilm"
      MapData: TagNumber= 0XA406 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneCaptureType"
      MapData: TagNumber= 0XA407 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "GainControl"
      MapData: TagNumber= 0XA408 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
      MapData: TagNumber= 0XA409 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
      MapData: TagNumber= 0XA40A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
      MapData: TagNumber= 0XC4A5 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Sony0xC4A5"
    MapIfd: Caption= "Ifd1"
     MapSubIfds: Count= 0
     MapDatas:
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Compression"
      MapData: TagNumber= 0X010F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Maker"
      MapData: TagNumber= 0X0110 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0112 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Rotate"
      MapData: TagNumber= 0X011A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "XResolution"
      MapData: TagNumber= 0X011B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YResolution"
      MapData: TagNumber= 0X0128 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ResolutionUnit"
      MapData: TagNumber= 0X0132 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X0201 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ThumbOffset"
      MapData: TagNumber= 0X0202 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ThumbLength"
      MapData: TagNumber= 0X0213 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YCBCRPositioning"
    MapIfd: Caption= "Exif"
     MapSubIfds: Count= 1
      MapSubIfd: Caption= "MakerNote" TagNumber= 0X927C IsPointer= 0 Seek= 8
     MapDatas:
      MapData: TagNumber= 0X829D Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 2 Caption= "Aperture"
      MapData: TagNumber= 0X829A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 3 Caption= "ExposureTime"
      MapData: TagNumber= 0X8822 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ExposureProgram"
      MapData: TagNumber= 0X8827 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 4 Caption= "Iso"
      MapData: TagNumber= 0X9000 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ExifVersion"
      MapData: TagNumber= 0X9003 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X9004 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DataTimeDigitized"
      MapData: TagNumber= 0X9101 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ComponentConfiguration"
      MapData: TagNumber= 0X9102 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CompressedBitsPerPixel"
      MapData: TagNumber= 0X9201 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 3 Formula= "ExposureTimeApex"          = "1/2^Value"
      MapData: TagNumber= 0X9202 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "APertureApex"              = "e^((Value*ln(2))/2)"
      MapData: TagNumber= 0X9203 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureValueApex"
      MapData: TagNumber= 0X9204 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureBiasApex"
      MapData: TagNumber= 0X9205 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Caption= "MaxApertureValue"
      MapData: TagNumber= 0X9206 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 6 Caption= "SubjectDistance"
      MapData: TagNumber= 0X9207 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "MeteringMode"
      MapData: TagNumber= 0X9208 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LightSource"
      MapData: TagNumber= 0X9209 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Flash"
      MapData: TagNumber= 0X920A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 5 Caption= "Focale"
      MapData: TagNumber= 0X927C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 0 Format= 0 Caption= "MakerNote"
      MapData: TagNumber= 0X9286 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "UserComment"
      MapData: TagNumber= 0X9290 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTime"
      MapData: TagNumber= 0X9291 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTimeOriginal"
      MapData: TagNumber= 0X9292 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTimeDigitized"
      MapData: TagNumber= 0XA000 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashPixVersion"
      MapData: TagNumber= 0XA001 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ColorSpace"
      MapData: TagNumber= 0XA002 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "PixelXDimension"
      MapData: TagNumber= 0XA003 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "PixelYDimension"
      MapData: TagNumber= 0XA004 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "RelatedSoundFile"
      MapData: TagNumber= 0XA005 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "InteroperabilityIfd"
      MapData: TagNumber= 0XA20E Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneXResolution"
      MapData: TagNumber= 0XA20F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneYResolution"
      MapData: TagNumber= 0XA210 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneResolutionUnit"
      MapData: TagNumber= 0XA217 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sensing"
      MapData: TagNumber= 0XA300 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FileSource"
      MapData: TagNumber= 0XA301 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneType"
      MapData: TagNumber= 0XA401 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CustomRendered"
      MapData: TagNumber= 0XA402 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureMode"
      MapData: TagNumber= 0XA403 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
      MapData: TagNumber= 0XA404 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoomRatio"
      MapData: TagNumber= 0XA405 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "FocalLengthIn35mmFilm"
      MapData: TagNumber= 0XA406 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneCaptureType"
      MapData: TagNumber= 0XA407 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "GainControl"
      MapData: TagNumber= 0XA408 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
      MapData: TagNumber= 0XA409 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
      MapData: TagNumber= 0XA40A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
      MapData: TagNumber= 0XA40C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SubjectDistanceType"
    MapIfd: Caption= "MakerNote"
     MapSubIfds: Count= 0
     MapDatas:
      Group: "ShootInfo" TagNumber= 0X0200
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ShootingMode"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SequenceNumber"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "PanoramaDirection"
      MapData: TagNumber= 0X0201 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "JpegQuality"
      MapData: TagNumber= 0X0202 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "MacroMode"
      MapData: TagNumber= 0X0203 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "BlackAndWhiteMode"
      MapData: TagNumber= 0X0204 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoom"
      MapData: TagNumber= 0X0209 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "CameraID"
      MapData: TagNumber= 0X020A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Comments"
      MapData: TagNumber= 0X020B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageWidth"
      MapData: TagNumber= 0X020C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageHeight"
      MapData: TagNumber= 0X020D Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "EpsonSoftware"
      MapData: TagNumber= 0X0300 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "PreCaptureFrames"
      MapData: TagNumber= 0X0F00 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DataDump"
  Model: Caption= "Canon" "Canon EOS 7D"
   Set: FlashFillInLight= -3.5
   Set: Sensor=14.9 22.3 "Canon APS-C" 18000000
   Set: ExposureTimeRange=0.000125 30.0
   Set: IsoRange=100.0 12800.0
   SetBitTag: Flash.Fired Exif Flash=*******1
   SetBitTag: Flash.Off MakerNote FlashBits=0000000000000000
   SetBitTag: Flash.BuiltIn  MakerNote FlashBits=**1*************
   SetBitTag: Flash.External MakerNote FlashBits=*1**************
   MapIfds: Count= 6
    MapIfd: Caption= "Ifd0"
     MapSubIfds: Count= 1
      MapSubIfd: Caption= "Exif" TagNumber= 0X8769 IsPointer= 1 Seek= 0
     MapDatas:
      MapData: TagNumber= 0X0100 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageWidth"
      MapData: TagNumber= 0X0101 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageHeight"
      Group: "BitSampleRGB" TagNumber= 0X0102
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleR"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleG"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleB"
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Compression"
      MapData: TagNumber= 0X010E Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageDesc"
      MapData: TagNumber= 0X010F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Maker"
      MapData: TagNumber= 0X0110 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0111 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewOffset"
      MapData: TagNumber= 0X0112 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Rotate"
      MapData: TagNumber= 0X0117 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewLength"
      MapData: TagNumber= 0X011A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "XResolution"
      MapData: TagNumber= 0X011B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YResolution"
      MapData: TagNumber= 0X0128 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ResolutionUnit"
      MapData: TagNumber= 0X0131 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Software"
      MapData: TagNumber= 0X0132 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X013B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Artist"
      MapData: TagNumber= 0X0213 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YCBCRPositioning"
      MapData: TagNumber= 0X8298 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Copyright"
      MapData: TagNumber= 0X8769 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 0 Format= 0 Caption= "Exif"
      MapData: TagNumber= 0X8825 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "GpsInfo"
      MapData: TagNumber= 0XA401 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "CustomRendered"
      MapData: TagNumber= 0XA402 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureMode"
      MapData: TagNumber= 0XA403 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
      MapData: TagNumber= 0XA404 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoomRatio"
      MapData: TagNumber= 0XA405 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalLengthIn35mmFilm"
      MapData: TagNumber= 0XA406 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneCaptureType"
      MapData: TagNumber= 0XA407 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "GainControl"
      MapData: TagNumber= 0XA408 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
      MapData: TagNumber= 0XA409 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
      MapData: TagNumber= 0XA40A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
      MapData: TagNumber= 0XC4A5 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Sony0xC4A5"
    MapIfd: Caption= "Ifd1"
     MapSubIfds: Count= 0
     MapDatas:
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Compression"
      MapData: TagNumber= 0X010F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Maker"
      MapData: TagNumber= 0X0110 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0112 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Rotate"
      MapData: TagNumber= 0X011A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "XResolution"
      MapData: TagNumber= 0X011B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YResolution"
      MapData: TagNumber= 0X0128 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ResolutionUnit"
      MapData: TagNumber= 0X0132 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X0201 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ThumbOffset"
      MapData: TagNumber= 0X0202 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ThumbLength"
      MapData: TagNumber= 0X0213 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YCBCRPositioning"
    MapIfd: Caption= "Ifd2"
     MapSubIfds: Count= 0
     MapDatas:
      MapData: TagNumber= 0X0100 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageWidth"
      MapData: TagNumber= 0X0101 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageHeight"
      Group: "BitSampleRGB" TagNumber= 0X0102
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleR"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleG"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleB"
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "RecordMode"
      MapData: TagNumber= 0X0106 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 0 Caption= "PhotometricInterpretation"
      MapData: TagNumber= 0X0111 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewOffset"
      MapData: TagNumber= 0X0115 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 0 Caption= "SamplesPerPixel"
      MapData: TagNumber= 0X0116 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 0 Caption= "RowsPerStrip"
      MapData: TagNumber= 0X0117 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewLength"
      MapData: TagNumber= 0X011C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 0 Caption= "PlanarConfiguration"
      MapData: TagNumber= 0XC5D9 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 0 Caption= "CanonTag0xC5D9"
      MapData: TagNumber= 0XC6C5 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 0 Caption= "CanonTag0xC6C5"
      MapData: TagNumber= 0XC6DC Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 0 Caption= "CanonTag0xC6DC"
    MapIfd: Caption= "Ifd3"
     MapSubIfds: Count= 0
     MapDatas:
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "RecordMode"
      MapData: TagNumber= 0X0111 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "RawOffset"
      MapData: TagNumber= 0X0117 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "RawLength"
      MapData: TagNumber= 0XC5D8 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CanonTag0xC5D8"
      MapData: TagNumber= 0XC5E0 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CanonTag0xC5E0"
      MapData: TagNumber= 0XC640 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CanonTag0xC640"
      MapData: TagNumber= 0XC6C5 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CanonTag0xC6C5"
    MapIfd: Caption= "Exif"
     MapSubIfds: Count= 1
      MapSubIfd: Caption= "MakerNote" TagNumber= 0X927C IsPointer= 0 Seek= 8
     MapDatas:
      MapData: TagNumber= 0X829D Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 2 Caption= "Aperture"
      MapData: TagNumber= 0X829A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 3 Caption= "ExposureTime"
      MapData: TagNumber= 0X8822 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ExposureProgram"
      MapData: TagNumber= 0X8827 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 4 Caption= "Iso"
      MapData: TagNumber= 0X9000 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ExifVersion"
      MapData: TagNumber= 0X9003 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X9004 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DataTimeDigitized"
      MapData: TagNumber= 0X9101 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ComponentConfiguration"
      MapData: TagNumber= 0X9102 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CompressedBitsPerPixel"
      MapData: TagNumber= 0X9201 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 3 Formula= "ExposureTimeApex"          = "1/2^Value"
      MapData: TagNumber= 0X9202 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "APertureApex"              = "e^((Value*ln(2))/2)"
      MapData: TagNumber= 0X9203 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureValueApex"
      MapData: TagNumber= 0X9204 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureBiasApex"
      MapData: TagNumber= 0X9205 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Caption= "MaxApertureValue"
      MapData: TagNumber= 0X9206 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 6 Caption= "SubjectDistance"
      MapData: TagNumber= 0X9207 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "MeteringMode"
      MapData: TagNumber= 0X9208 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LightSource"
      MapData: TagNumber= 0X9209 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Flash"
      MapData: TagNumber= 0X920A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 5 Caption= "Focale"
      MapData: TagNumber= 0X927C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 0 Format= 0 Caption= "MakerNote"
      MapData: TagNumber= 0X9286 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "UserComment"
      MapData: TagNumber= 0X9290 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTime"
      MapData: TagNumber= 0X9291 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTimeOriginal"
      MapData: TagNumber= 0X9292 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTimeDigitized"
      MapData: TagNumber= 0XA000 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashPixVersion"
      MapData: TagNumber= 0XA001 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ColorSpace"
      MapData: TagNumber= 0XA002 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "PixelXDimension"
      MapData: TagNumber= 0XA003 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "PixelYDimension"
      MapData: TagNumber= 0XA004 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "RelatedSoundFile"
      MapData: TagNumber= 0XA005 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "InteroperabilityIfd"
      MapData: TagNumber= 0XA20E Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneXResolution"
      MapData: TagNumber= 0XA20F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneYResolution"
      MapData: TagNumber= 0XA210 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneResolutionUnit"
      MapData: TagNumber= 0XA217 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sensing"
      MapData: TagNumber= 0XA300 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FileSource"
      MapData: TagNumber= 0XA301 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneType"
      MapData: TagNumber= 0XA401 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CustomRendered"
      MapData: TagNumber= 0XA402 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureMode"
      MapData: TagNumber= 0XA403 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
      MapData: TagNumber= 0XA404 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoomRatio"
      MapData: TagNumber= 0XA405 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "FocalLengthIn35mmFilm"
      MapData: TagNumber= 0XA406 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneCaptureType"
      MapData: TagNumber= 0XA407 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "GainControl"
      MapData: TagNumber= 0XA408 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
      MapData: TagNumber= 0XA409 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
      MapData: TagNumber= 0XA40A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
      MapData: TagNumber= 0XA40C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SubjectDistanceType"
    MapIfd: Caption= "MakerNote"
     MapSubIfds: Count= 0
     MapDatas:
      Group: "CanonCameraSettings" TagNumber= 0X0001
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DataLength"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "MacroMode"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Formula= "SelfTimer"           = "Value/10"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Quality"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FlashMode"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ContinuousDrive"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "FocusMode"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "RecordMode"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageSize"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "EasyMode"
       MapData: Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoom"
       MapData: Index=  13 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
       MapData: Index=  14 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
       MapData: Index=  15 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
       MapData: Index=  16 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ISOSpeed"
       MapData: Index=  17 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "MeteringMode"
       MapData: Index=  18 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocusRange"
       MapData: Index=  19 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AFPoint"
       MapData: Index=  20 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ExposureProgram"
       MapData: Index=  22 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LensType"
       MapData: Index=  23 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "LongFocal"
       MapData: Index=  24 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "ShortFocal"
       MapData: Index=  25 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalUnits"
       MapData: Index=  26 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "MaxApertureApex"     = "(Value/64)^2"
       MapData: Index=  27 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "MinApertureApex"     = "(Value/64)^2"
       MapData: Index=  28 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FlashActivity"
       MapData: Index=  29 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "FlashBits"
       MapData: Index=  32 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ContinuousDrive"
       MapData: Index=  33 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AESetting"
       MapData: Index=  34 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageStabilization"
       MapData: Index=  35 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DisplayAperture"
       MapData: Index=  36 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ZoomSourceWidth"
       MapData: Index=  37 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ZoomTargetWidth"
       MapData: Index=  39 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SpotMeteringMode"
       MapData: Index=  40 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "PhotoEffect"
       MapData: Index=  41 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ManualFlashOutput"
       MapData: Index=  42 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ColorTone"
       MapData: Index=  46 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SRAWQuality"
      Group: "CanonFocalInfo" TagNumber= 0X0002
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalType"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "FocalLength"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalPlaneXSize"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalPlaneYSize"
      Group: "CanonFlashInfo?" TagNumber= 0X0003
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashInfo1"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashInfo2"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashInfo3"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashInfo4"
      Group: "CanonShotInfo" TagNumber= 0X0004
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DataLength"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AutoISO"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Formula= "BaseISO"          = "50*(Value/32-4)^2"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Formula= "MesuredEV"        = "Value/20"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "ApertureApex"     = "(Value/64)^2"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 3 Formula= "ExposureTimeApex" = "(1/(Value/32)^2)"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureCompensation"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SlowShutter"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SequenceNumber"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "OpticalZoomCode"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Formula= "CameraTemperature"     = "Value/10"
       MapData: Index=  13 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashGuideNumber"
       MapData: Index=  14 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AFPointsInFocus"
       MapData: Index=  15 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "FlashBias"
       MapData: Index=  16 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AutoExposureBracketing"
       MapData: Index=  17 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AEBBracketValue"
       MapData: Index=  18 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ControlMode"
       MapData: Index=  19 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Unused"
       MapData: Index=  20 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Unused"
       MapData: Index=  21 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "Aperture"              = "(Value/64)^2"
       MapData: Index=  22 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 3 Formula= "ExposureTime"          = "(1/(Value/32)^2)"
       MapData: Index=  23 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 0 Format= 1 Formula= "MeasuredEV1"           = "(Value/8)-6"
       MapData: Index=  24 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "BulbDuration"
       MapData: Index=  25 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  26 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "CameraType"
       MapData: Index=  27 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AutoRotate"
       MapData: Index=  28 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "NDFilter"
       MapData: Index=  29 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SelfTimer2"
       MapData: Index=  30 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  31 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  32 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  33 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashOutput"
      MapData: TagNumber= 0X0006 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0009 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "OwnerName"
      MapData: TagNumber= 0X000C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SerialNumber"
      Group: "CanonCameraInfo_EOS_7D" TagNumber= 0X000D
       MapData: Index=   0 ForceType= 3 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CameraInfoCanon7D"
       MapData: Index=   1 ForceType= 1 SubOffest= 0X00000002 Used= 0 Dump= 1 Format= 3 Formula= "TargetExposureTimeApex" = "(1/(Value/32)^2)"
       MapData: Index=   2 ForceType= 1 SubOffest= 0X00000003 Used= 0 Dump= 1 Format= 2 Formula= "TargetApertureApex"     = "e^(((Value/10)*ln(2))/2)"
       MapData: Index=   3 ForceType= 1 SubOffest= 0X00000004 Used= 0 Dump= 1 Format= 3 Formula= "ExposureTime"           = "(1/(Value/32)^2)"
       MapData: Index=   4 ForceType= 1 SubOffest= 0X00000005 Used= 0 Dump= 1 Format= 2 Formula= "ApertureApexUnit"       = "e^(((Value/10)*ln(2))/2)"
       MapData: Index=   5 ForceType= 1 SubOffest= 0X00000006 Used= 0 Dump= 1 Format= 1 Formula= "ISOApexUnit"            = "50*((Value/32)-4)^2"
       MapData: Index=   6 ForceType= 1 SubOffest= 0X00000007 Used= 0 Dump= 1 Format= 1 Caption= "HighlightTonePriority"
       MapData: Index=   7 ForceType= 1 SubOffest= 0X00000008 Used= 1 Dump= 1 Format= 1 Formula= "MeasuredEV2"            = "(Value/10)-1.5"
       MapData: Index=   8 ForceType= 1 SubOffest= 0X00000009 Used= 1 Dump= 1 Format= 1 Formula= "MeasuredEV"             = "(Value/10)-1.5"
       MapData: Index=   9 ForceType= 1 SubOffest= 0X00000015 Used= 0 Dump= 1 Format= 1 Caption= "FlashMeteringMode"
       MapData: Index=  10 ForceType= 1 SubOffest= 0X00000019 Used= 0 Dump= 1 Format= 1 Formula= "CameraTemperature"      = "Value/10"
       MapData: Index=  11 ForceType= 1 SubOffest= 0X0000001F Used= 0 Dump= 1 Format= 1 Caption= "FocalLength"
      MapData: TagNumber= 0X0007 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Firmware"
      Group: "CustomFunctions_EOS_7D" TagNumber= 0X000F
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DataLength"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SetButtonCrossKeysFunc"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LongExposureNoiseReduction"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FlashSyncSpeedAv"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Shutter-AELock"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AFAssistBeam"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureLevelIncrements"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "MirrorLockup"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ETTLII"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ShutterCurtainSync"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "MagnifiedView"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "LCDDisplayAtPowerOn"
      MapData: TagNumber= 0X0010 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CanonModelId"
      MapData: TagNumber= 0X0013 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ThumbnailImageValidArea"
      MapData: TagNumber= 0X0015 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SerialNumberFormat"
      MapData: TagNumber= 0X0019 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
      Group: "CanonAFInfo2_EOS_7D" TagNumber= 0X0026
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DataLength"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "FocusAreaMode"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "NumAFPoints"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ValidAFPoints"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageWidth"  
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageHeight"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFImageWidth"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFImageHeight"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFAreaWidth"
       MapData: Index=  27 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFAreaHeight"
       MapData: Index=  46 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFAreaXPositions"
       MapData: Index=  65 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFAreaYPositions"
      MapData: TagNumber= 0X0083 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "OriginalDecisionDataOffset"
      Group: "CanonFileInfo_EOS_7D" TagNumber= 0X0093
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DataLength"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Unused"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Unused"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "BracketMode"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BracketValue"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BracketShotNumber"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "RawJpgQuality"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "RawJpgSize"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LongExposureNoiseReduction2"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WBBracketMode"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "WBBracketValueAB"
       MapData: Index=  13 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "WBBracketValueGM"
       MapData: Index=  14 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FilterEffect"
       MapData: Index=  15 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ToningEffect"
       MapData: Index=  16 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MacroMagnification"
       MapData: Index=  17 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MacroMagnification"
       MapData: Index=  18 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MacroMagnification"
       MapData: Index=  19 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MacroMagnification"
       MapData: Index=  20 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Formula= "FocusDistanceUpper" = "Value/100"
       MapData: Index=  21 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Formula= "FocusDistanceLower" = "Value/100"
       MapData: Index=  22 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  23 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  24 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  25 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
      MapData: TagNumber= 0X0095 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Lens"
      MapData: TagNumber= 0X0096 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "InternalSerialNumber"
      MapData: TagNumber= 0X0097 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "DustRemovalData"
      MapData: TagNumber= 0X0098 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CropInfo"
      MapData: TagNumber= 0X0099 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
      MapData: TagNumber= 0X009A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
      Group: "ProcessingInfo" TagNumber= 0X00A0
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Length"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ToneCurve"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SharpnessFrequency"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorRedLevel"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorBlueLevel"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "WhiteBalanceRed"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "WhiteBalanceBlue"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "WhiteBalance"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ColorTemperature"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "PictureStyle"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DigitalGain"
       MapData: Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "WBShiftAB"
       MapData: Index=  13 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "WBShiftGM"
      Group: "MeasuredColor" TagNumber= 0X00AA
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Length"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MeasuredColor.1"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MeasuredColor.2"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MeasuredColor.3"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MeasuredColor.4"
      MapData: TagNumber= 0X00B4 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ColorSpace"
      MapData: TagNumber= 0X00D0 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "VRDOffset"
      Group: "SensorInfo" TagNumber= 0X00E0
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Length"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorWidth"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorHeight"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorLeftBorder"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorTopBorder"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorRightBorder"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorBottomBorder"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BlackMaskLeftBorder"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BlackMaskTopBorder"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BlackMaskRightBorder"
       MapData: Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BlackMaskBottomBorder"
       MapData: Index=  15 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfo???"
       MapData: Index=  16 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfo???"
      MapData: TagNumber= 0X4001 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "ColorData"
      MapData: TagNumber= 0X4002 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "CRWParam"
      MapData: TagNumber= 0X4005 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "ColorInfo"
      MapData: TagNumber= 0X4008 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "BlackLevel"
      MapData: TagNumber= 0X4009 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "???"
      MapData: TagNumber= 0X4010 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "CustomPictureStyleFileName"
      MapData: TagNumber= 0X4011 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "0x4011NoDump"
      MapData: TagNumber= 0X4012 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "???"
      MapData: TagNumber= 0X4013 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "AFMicroAdj"
      MapData: TagNumber= 0X4015 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "VignettingCorr"
      MapData: TagNumber= 0X4016 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "VignettingCorr2"
      MapData: TagNumber= 0X4017 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "???"
      MapData: TagNumber= 0X4018 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "LightingOpt"
      MapData: TagNumber= 0X4019 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "LensInfo"
  Model: Caption= "Canon" "Canon EOS 400D DIGITAL"
   Set: FlashFillInLight= -3.5
   Set: Sensor=14.9 22.3 "Canon APS-C" 10100000
   Set: ExposureTimeRange=0.00025 30
   Set: IsoRange=100.0 3200.0
   SetBitTag: Flash.Fired Exif Flash=*******1
   SetBitTag: Flash.Off MakerNote FlashBits=0000000000000000
   SetBitTag: Flash.BuiltIn  MakerNote FlashBits=**1*************
   SetBitTag: Flash.External MakerNote FlashBits=*1**************
   MapIfds: Count= 6
    MapIfd: Caption= "Ifd0"
     MapSubIfds: Count= 1
      MapSubIfd: Caption= "Exif" TagNumber= 0X8769 IsPointer= 1 Seek= 0
     MapDatas:
      MapData: TagNumber= 0X0100 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageWidth"
      MapData: TagNumber= 0X0101 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageHeight"
      Group: "BitSampleRGB" TagNumber= 0X0102
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleR"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleG"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleB"
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Compression"
      MapData: TagNumber= 0X010E Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageDesc"
      MapData: TagNumber= 0X010F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Maker"
      MapData: TagNumber= 0X0110 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0111 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewOffset"
      MapData: TagNumber= 0X0112 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Rotate"
      MapData: TagNumber= 0X0117 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewLength"
      MapData: TagNumber= 0X011A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "XResolution"
      MapData: TagNumber= 0X011B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YResolution"
      MapData: TagNumber= 0X0128 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ResolutionUnit"
      MapData: TagNumber= 0X0131 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Software"
      MapData: TagNumber= 0X0132 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X013B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Artist"
      MapData: TagNumber= 0X0213 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YCBCRPositioning"
      MapData: TagNumber= 0X8298 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Copyright"
      MapData: TagNumber= 0X8769 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 0 Format= 0 Caption= "Exif"
      MapData: TagNumber= 0X8825 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "GpsInfo"
      MapData: TagNumber= 0XA401 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "CustomRendered"
      MapData: TagNumber= 0XA402 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureMode"
      MapData: TagNumber= 0XA403 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
      MapData: TagNumber= 0XA404 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoomRatio"
      MapData: TagNumber= 0XA405 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalLengthIn35mmFilm"
      MapData: TagNumber= 0XA406 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneCaptureType"
      MapData: TagNumber= 0XA407 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "GainControl"
      MapData: TagNumber= 0XA408 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
      MapData: TagNumber= 0XA409 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
      MapData: TagNumber= 0XA40A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
      MapData: TagNumber= 0XC4A5 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Sony0xC4A5"
    MapIfd: Caption= "Ifd1"
     MapSubIfds: Count= 0
     MapDatas:
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Compression"
      MapData: TagNumber= 0X010F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Maker"
      MapData: TagNumber= 0X0110 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0112 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Rotate"
      MapData: TagNumber= 0X011A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "XResolution"
      MapData: TagNumber= 0X011B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YResolution"
      MapData: TagNumber= 0X0128 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ResolutionUnit"
      MapData: TagNumber= 0X0132 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X0201 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ThumbOffset"
      MapData: TagNumber= 0X0202 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ThumbLength"
      MapData: TagNumber= 0X0213 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YCBCRPositioning"
    MapIfd: Caption= "Ifd2"
     MapSubIfds: Count= 0
     MapDatas:
    MapIfd: Caption= "Ifd3"
     MapSubIfds: Count= 0
     MapDatas:
    MapIfd: Caption= "Exif"
     MapSubIfds: Count= 1
      MapSubIfd: Caption= "MakerNote" TagNumber= 0X927C IsPointer= 0 Seek= 8
     MapDatas:
      MapData: TagNumber= 0X829D Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 2 Caption= "Aperture"
      MapData: TagNumber= 0X829A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 3 Caption= "ExposureTime"
      MapData: TagNumber= 0X8822 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ExposureProgram"
      MapData: TagNumber= 0X8827 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 4 Caption= "Iso"
      MapData: TagNumber= 0X9000 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ExifVersion"
      MapData: TagNumber= 0X9003 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X9004 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DataTimeDigitized"
      MapData: TagNumber= 0X9101 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ComponentConfiguration"
      MapData: TagNumber= 0X9102 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CompressedBitsPerPixel"
      MapData: TagNumber= 0X9201 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 3 Formula= "ExposureTimeApex"          = "1/2^Value"
      MapData: TagNumber= 0X9202 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "APertureApex"              = "e^((Value*ln(2))/2)"
      MapData: TagNumber= 0X9203 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureValueApex"
      MapData: TagNumber= 0X9204 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureBiasApex"
      MapData: TagNumber= 0X9205 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Caption= "MaxApertureValue"
      MapData: TagNumber= 0X9206 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 6 Caption= "SubjectDistance"
      MapData: TagNumber= 0X9207 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "MeteringMode"
      MapData: TagNumber= 0X9208 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LightSource"
      MapData: TagNumber= 0X9209 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Flash"
      MapData: TagNumber= 0X920A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 5 Caption= "Focale"
      MapData: TagNumber= 0X927C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 0 Format= 0 Caption= "MakerNote"
      MapData: TagNumber= 0X9286 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "UserComment"
      MapData: TagNumber= 0X9290 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTime"
      MapData: TagNumber= 0X9291 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTimeOriginal"
      MapData: TagNumber= 0X9292 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTimeDigitized"
      MapData: TagNumber= 0XA000 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashPixVersion"
      MapData: TagNumber= 0XA001 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ColorSpace"
      MapData: TagNumber= 0XA002 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "PixelXDimension"
      MapData: TagNumber= 0XA003 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "PixelYDimension"
      MapData: TagNumber= 0XA004 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "RelatedSoundFile"
      MapData: TagNumber= 0XA005 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "InteroperabilityIfd"
      MapData: TagNumber= 0XA20E Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneXResolution"
      MapData: TagNumber= 0XA20F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneYResolution"
      MapData: TagNumber= 0XA210 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneResolutionUnit"
      MapData: TagNumber= 0XA217 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sensing"
      MapData: TagNumber= 0XA300 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FileSource"
      MapData: TagNumber= 0XA301 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneType"
      MapData: TagNumber= 0XA401 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CustomRendered"
      MapData: TagNumber= 0XA402 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureMode"
      MapData: TagNumber= 0XA403 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
      MapData: TagNumber= 0XA404 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoomRatio"
      MapData: TagNumber= 0XA405 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "FocalLengthIn35mmFilm"
      MapData: TagNumber= 0XA406 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneCaptureType"
      MapData: TagNumber= 0XA407 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "GainControl"
      MapData: TagNumber= 0XA408 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
      MapData: TagNumber= 0XA409 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
      MapData: TagNumber= 0XA40A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
      MapData: TagNumber= 0XA40C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SubjectDistanceType"
    MapIfd: Caption= "MakerNote"
     MapSubIfds: Count= 0
     MapDatas:
      Group: "CameraSettings1_1" TagNumber= 0X0001
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "0x0001Length"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "MacroMode"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SelfTimer"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Quality"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FlashMode"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ContinuousDrive"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "FocusMode"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "RecordMode"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageSize"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "EasyMode"
       MapData: Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoom"
       MapData: Index=  13 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
       MapData: Index=  14 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
       MapData: Index=  15 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
       MapData: Index=  16 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ISOSpeed"
       MapData: Index=  17 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "MeteringMode"
       MapData: Index=  18 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocusRange"
       MapData: Index=  19 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AFPoint"
       MapData: Index=  20 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ExposureMode"
       MapData: Index=  22 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LensType"
       MapData: Index=  23 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "LongFocal"
       MapData: Index=  24 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "ShortFocal"
       MapData: Index=  25 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalUnits"
       MapData: Index=  26 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "MaxApertureApex" = "(Value/64)^2"
       MapData: Index=  27 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "MinApertureApex" = "(Value/64)^2"
       MapData: Index=  28 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FlashActivity"
       MapData: Index=  29 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "FlashBits"
       MapData: Index=  32 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ContinuousDrive"
       MapData: Index=  33 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AESetting"
       MapData: Index=  34 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageStabilization"
       MapData: Index=  35 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DisplayAperture"
       MapData: Index=  36 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ZoomSourceWidth"
       MapData: Index=  37 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ZoomTargetWidth"
       MapData: Index=  39 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SpotMeteringMode"
       MapData: Index=  40 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "PhotoEffect"
       MapData: Index=  41 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ManualFlashOutput"
       MapData: Index=  42 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ColorTone"
       MapData: Index=  46 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SRAWQuality"
      Group: "CameraSettings1_2" TagNumber= 0X0002
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalType"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "FocalLength"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneXSize"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneYSize"
      Group: "CameraSettings1_3" TagNumber= 0X0003
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashInfo1"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashInfo2"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashInfo3"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashInfo4"
      Group: "CameraSettings2" TagNumber= 0X0004
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "0x0004Length"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AutoISO"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 4 Formula= "BaseISOApex"            = "50*(Value/32-4)^2"  
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "MeasuredEV"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "TargetApertureApex"     = "(Value/64)^2"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 3 Formula= "TargetExposureTimeApex" = "(1/(Value/32)^2)"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureCompensation"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SlowShutter"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SequenceNumber"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "OpticalZoomCode"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Formula= "CameraTemperature"   = "Value/10"
       MapData: Index=  13 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashGuideNumber"
       MapData: Index=  14 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AFPointsInFocus"
       MapData: Index=  15 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FlashBias"
       MapData: Index=  16 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AutoExposureBracketing"
       MapData: Index=  17 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AEBBracketValue"
       MapData: Index=  18 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ControlMode"
       MapData: Index=  19 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 6 Formula= "FocusDistanceLower"  = "Value/100"
       MapData: Index=  20 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 6 Formula= "FocusDistanceUpper"  = "Value/100"
       MapData: Index=  21 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "FNumber"             = "(Value/64)^2"
       MapData: Index=  22 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 3 Formula= "ExposureTime"        = "(1/(Value/32)^2)"
       MapData: Index=  23 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 7 Formula= "MeasuredEV2"         = "(Value/10)-2"
       MapData: Index=  24 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "BulbDuration"
       MapData: Index=  25 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  26 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "CameraType"
       MapData: Index=  27 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AutoRotate"
       MapData: Index=  28 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "NDFilter"
       MapData: Index=  29 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SelfTimer2"
       MapData: Index=  30 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  31 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  32 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  33 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FlashOutput"
      MapData: TagNumber= 0X0006 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0009 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "OwnerName"
      MapData: TagNumber= 0X000C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SerialNumber"
      MapData: TagNumber= 0X0007 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Firmware"
      Group: "CameraSettings3" TagNumber= 0X000F
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "0x000FLength"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SetButtonCrossKeysFunc"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LongExposureNoiseReduction"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FlashSyncSpeedAv"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Shutter-AELock"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AFAssistBeam"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureLevelIncrements"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "MirrorLockup"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ETTLII"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ShutterCurtainSync"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "MagnifiedView"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LCDDisplayAtPowerOn"
      MapData: TagNumber= 0X0010 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "CanonModelId"
      Group: "AFInfo" TagNumber= 0X0012
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "NumAFPoints"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ValidAFPoints"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageWidth"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageHeight"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFImageWidth"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFImageHeight"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFAreaWidth"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFAreaHeight"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFAreaXPositions"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Xpt2"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Xpt3"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Xpt4"
       MapData: Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Xpt5"
       MapData: Index=  13 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Xpt6"
       MapData: Index=  14 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Xpt7"
       MapData: Index=  15 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Xpt8"
       MapData: Index=  16 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Xpt9"
       MapData: Index=  17 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFAreaYPositions"
       MapData: Index=  18 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Ypt2"
       MapData: Index=  19 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Ypt3"
       MapData: Index=  20 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Ypt4"
       MapData: Index=  21 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Ypt5"
       MapData: Index=  22 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Ypt6"
       MapData: Index=  23 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Ypt7"
       MapData: Index=  24 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Ypt8"
       MapData: Index=  25 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Ypt9"
       MapData: Index=  26 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AFPointsInFocus"
       MapData: Index=  27 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "PrimaryAFPoint"
      MapData: TagNumber= 0X0013 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ThumbnailImageValidArea"
      MapData: TagNumber= 0X0015 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SerialNumberFormat"
      MapData: TagNumber= 0X0019 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
      MapData: TagNumber= 0X0083 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "OriginalDecisionDataOffset"
      MapData: TagNumber= 0X0093 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "0x0093Length"
      MapData: TagNumber= 0X0093 Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ShutterCountBytesLow"
      MapData: TagNumber= 0X0093 Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ShutterCountBytesHigth"
      MapData: TagNumber= 0X0093 Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "BracketMode"
      MapData: TagNumber= 0X0093 Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "BracketValue"
      MapData: TagNumber= 0X0093 Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "BracketShotNumber"
      MapData: TagNumber= 0X0093 Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "RawJpgQuality"
      MapData: TagNumber= 0X0093 Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "RawJpgSize"
      MapData: TagNumber= 0X0093 Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LongExposureNoiseReduction2"
      MapData: TagNumber= 0X0093 Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WBBracketMode"
      MapData: TagNumber= 0X0093 Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
      MapData: TagNumber= 0X0093 Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
      MapData: TagNumber= 0X0093 Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WBBracketValueAB"
      MapData: TagNumber= 0X0093 Index=  13 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WBBracketValueGM"
      MapData: TagNumber= 0X0093 Index=  14 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FilterEffect"
      MapData: TagNumber= 0X0093 Index=  15 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ToningEffect"
      MapData: TagNumber= 0X0093 Index=  16 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "MacroMagnification"
      MapData: TagNumber= 0X0095 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Lens"
      MapData: TagNumber= 0X0096 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "InternalSerialNumber"
      MapData: TagNumber= 0X0097 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DustRemovalData"
      MapData: TagNumber= 0X0098 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CropInfo"
      MapData: TagNumber= 0X00A0 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ProcessingInfoLength"
      MapData: TagNumber= 0X00A0 Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ProcessingInfoToneCurve"
      MapData: TagNumber= 0X00A0 Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ProcessingInfoSharpness"
      MapData: TagNumber= 0X00A0 Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ProcessingInfoSharpnessFrequency"
      MapData: TagNumber= 0X00A0 Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ProcessingInfoSensorRedLevel"
      MapData: TagNumber= 0X00A0 Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ProcessingInfoSensorBlueLevel"
      MapData: TagNumber= 0X00A0 Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ProcessingInfoWhiteBalanceRed"
      MapData: TagNumber= 0X00A0 Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ProcessingInfoWhiteBalanceBlue"
      MapData: TagNumber= 0X00A0 Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ProcessingInfoWhiteBalance"
      MapData: TagNumber= 0X00A0 Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ProcessingInfoColorTemperature"
      MapData: TagNumber= 0X00A0 Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ProcessingInfoPictureStyle"
      MapData: TagNumber= 0X00A0 Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ProcessingInfoDigitalGain"
      MapData: TagNumber= 0X00A0 Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ProcessingInfoWBShiftAB"
      MapData: TagNumber= 0X00A0 Index=  13 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ProcessingInfoWBShiftGM"
      MapData: TagNumber= 0X00AA Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MeasuredColorLength"
      MapData: TagNumber= 0X00AA Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MeasuredColor1"
      MapData: TagNumber= 0X00AA Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MeasuredColor2"
      MapData: TagNumber= 0X00AA Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MeasuredColor3"
      MapData: TagNumber= 0X00AA Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MeasuredColor4"
      MapData: TagNumber= 0X00B4 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ColorSpace"
      MapData: TagNumber= 0X00D0 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "VRDOffset"
      MapData: TagNumber= 0X00E0 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfoLength"
      MapData: TagNumber= 0X00E0 Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfoSensorWidth"
      MapData: TagNumber= 0X00E0 Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfoSensorHeight"
      MapData: TagNumber= 0X00E0 Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfo???"
      MapData: TagNumber= 0X00E0 Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfo???"
      MapData: TagNumber= 0X00E0 Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfoSensorLeftBorder"
      MapData: TagNumber= 0X00E0 Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfoSensorTopBorder"
      MapData: TagNumber= 0X00E0 Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfoSensorRightBorder"
      MapData: TagNumber= 0X00E0 Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfoSensorBottomBorder"
      MapData: TagNumber= 0X00E0 Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfoBlackMaskLeftBorder"
      MapData: TagNumber= 0X00E0 Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfoBlackMaskTopBorder"
      MapData: TagNumber= 0X00E0 Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfoBlackMaskRightBorder"
      MapData: TagNumber= 0X00E0 Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfoBlackMaskBottomBorder"
      MapData: TagNumber= 0X00E0 Index=  13 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfo???"
      MapData: TagNumber= 0X00E0 Index=  14 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfo???"
      MapData: TagNumber= 0X00E0 Index=  15 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfo???"
      MapData: TagNumber= 0X00E0 Index=  16 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfo???"
      MapData: TagNumber= 0X4001 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "ColorData"
      MapData: TagNumber= 0X4008 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "BlackLevel"
      MapData: TagNumber= 0X4009 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "???"
      MapData: TagNumber= 0X4010 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CustomPictureStyleFileName"
      MapData: TagNumber= 0X4011 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "0x4011NoDump"
  Model: Caption= "Canon" "Canon EOS 5D Mark II"
   Set: FlashFillInLight= -3.5
   Set: Sensor=24.0 36.0 "FullFrame" 21000000
   Set: ExposureTimeRange=0.000125 30
   Set: IsoRange=50.0 12800.0
   SetBitTag: Flash.Fired Exif Flash=*******1
   SetBitTag: Flash.Off MakerNote FlashBits=0000000000000000
   SetBitTag: Flash.BuiltIn  MakerNote FlashBits=**1*************
   SetBitTag: Flash.External MakerNote FlashBits=*1**************
   MapIfds: Count= 6
    MapIfd: Caption= "Ifd0"
     MapSubIfds: Count= 1
      MapSubIfd: Caption= "Exif" TagNumber= 0X8769 IsPointer= 1 Seek= 0
     MapDatas:
      MapData: TagNumber= 0X0100 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageWidth"
      MapData: TagNumber= 0X0101 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageHeight"
      Group: "BitSampleRGB" TagNumber= 0X0102
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleR"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleG"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleB"
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Compression"
      MapData: TagNumber= 0X010E Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageDesc"
      MapData: TagNumber= 0X010F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Maker"
      MapData: TagNumber= 0X0110 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0111 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewOffset"
      MapData: TagNumber= 0X0112 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Rotate"
      MapData: TagNumber= 0X0117 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewLength"
      MapData: TagNumber= 0X011A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "XResolution"
      MapData: TagNumber= 0X011B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YResolution"
      MapData: TagNumber= 0X0128 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ResolutionUnit"
      MapData: TagNumber= 0X0131 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Software"
      MapData: TagNumber= 0X0132 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X013B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Artist"
      MapData: TagNumber= 0X0213 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YCBCRPositioning"
      MapData: TagNumber= 0X8298 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Copyright"
      MapData: TagNumber= 0X8769 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 0 Format= 0 Caption= "Exif"
      MapData: TagNumber= 0X8825 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "GpsInfo"
      MapData: TagNumber= 0XA401 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "CustomRendered"
      MapData: TagNumber= 0XA402 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureMode"
      MapData: TagNumber= 0XA403 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
      MapData: TagNumber= 0XA404 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoomRatio"
      MapData: TagNumber= 0XA405 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalLengthIn35mmFilm"
      MapData: TagNumber= 0XA406 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneCaptureType"
      MapData: TagNumber= 0XA407 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "GainControl"
      MapData: TagNumber= 0XA408 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
      MapData: TagNumber= 0XA409 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
      MapData: TagNumber= 0XA40A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
      MapData: TagNumber= 0XC4A5 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Sony0xC4A5"
    MapIfd: Caption= "Ifd1"
     MapSubIfds: Count= 0
     MapDatas:
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Compression"
      MapData: TagNumber= 0X010F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Maker"
      MapData: TagNumber= 0X0110 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0112 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "Rotate"
      MapData: TagNumber= 0X011A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "XResolution"
      MapData: TagNumber= 0X011B Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YResolution"
      MapData: TagNumber= 0X0128 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ResolutionUnit"
      MapData: TagNumber= 0X0132 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X0201 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ThumbOffset"
      MapData: TagNumber= 0X0202 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ThumbLength"
      MapData: TagNumber= 0X0213 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "YCBCRPositioning"
    MapIfd: Caption= "Ifd2"
     MapSubIfds: Count= 0
     MapDatas:
      MapData: TagNumber= 0X0100 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageWidth"
      MapData: TagNumber= 0X0101 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ImageHeight"
      Group: "BitSampleRGB" TagNumber= 0X0102
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleR"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleG"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BitSampleB"
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "RecordMode"
      MapData: TagNumber= 0X0106 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 0 Caption= "PhotometricInterpretation"
      MapData: TagNumber= 0X0111 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewOffset"
      MapData: TagNumber= 0X0115 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 0 Caption= "SamplesPerPixel"
      MapData: TagNumber= 0X0116 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 0 Caption= "RowsPerStrip"
      MapData: TagNumber= 0X0117 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "PreviewLength"
      MapData: TagNumber= 0X011C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 0 Caption= "PlanarConfiguration"
      MapData: TagNumber= 0XC5D9 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 0 Caption= "CanonTag0xC5D9"
      MapData: TagNumber= 0XC6C5 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 0 Caption= "CanonTag0xC6C5"
      MapData: TagNumber= 0XC6DC Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 0 Caption= "CanonTag0xC6DC"
    MapIfd: Caption= "Ifd3"
     MapSubIfds: Count= 0
     MapDatas:
      MapData: TagNumber= 0X0103 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "RecordMode"
      MapData: TagNumber= 0X0111 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "RawOffset"
      MapData: TagNumber= 0X0117 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "RawLength"
      MapData: TagNumber= 0XC5D8 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CanonTag0xC5D8"
      MapData: TagNumber= 0XC5E0 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CanonTag0xC5E0"
      MapData: TagNumber= 0XC640 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CanonTag0xC640"
      MapData: TagNumber= 0XC6C5 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CanonTag0xC6C5"
    MapIfd: Caption= "Exif"
     MapSubIfds: Count= 1
      MapSubIfd: Caption= "MakerNote" TagNumber= 0X927C IsPointer= 0 Seek= 0
     MapDatas:
      MapData: TagNumber= 0X829D Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 2 Caption= "Aperture"
      MapData: TagNumber= 0X829A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 3 Caption= "ExposureTime"
      MapData: TagNumber= 0X8822 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ExposureProgram"
      MapData: TagNumber= 0X8827 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 4 Caption= "Iso"
      MapData: TagNumber= 0X9000 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ExifVersion"
      MapData: TagNumber= 0X9003 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "DateTimeOriginal"
      MapData: TagNumber= 0X9004 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DataTimeDigitized"
      MapData: TagNumber= 0X9101 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ComponentConfiguration"
      MapData: TagNumber= 0X9102 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CompressedBitsPerPixel"
      MapData: TagNumber= 0X9201 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 3 Formula= "ExposureTimeApex"          = "1/2^Value"
      MapData: TagNumber= 0X9202 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "APertureApex"              = "e^((Value*ln(2))/2)"
      MapData: TagNumber= 0X9203 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureValueApex"
      MapData: TagNumber= 0X9204 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureBiasApex"
      MapData: TagNumber= 0X9205 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Caption= "MaxApertureValue"
      MapData: TagNumber= 0X9206 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 6 Caption= "SubjectDistance"
      MapData: TagNumber= 0X9207 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 1 Caption= "MeteringMode"
      MapData: TagNumber= 0X9208 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LightSource"
      MapData: TagNumber= 0X9209 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Flash"
      MapData: TagNumber= 0X920A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 1 Format= 5 Caption= "Focale"
      MapData: TagNumber= 0X927C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 2 Dump= 0 Format= 0 Caption= "MakerNote"
      MapData: TagNumber= 0X9286 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "UserComment"
      MapData: TagNumber= 0X9290 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTime"
      MapData: TagNumber= 0X9291 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTimeOriginal"
      MapData: TagNumber= 0X9292 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SubSecTimeDigitized"
      MapData: TagNumber= 0XA000 Index=   0 ForceType= 4 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashPixVersion"
      MapData: TagNumber= 0XA001 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ColorSpace"
      MapData: TagNumber= 0XA002 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "PixelXDimension"
      MapData: TagNumber= 0XA003 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "PixelYDimension"
      MapData: TagNumber= 0XA004 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "RelatedSoundFile"
      MapData: TagNumber= 0XA005 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "InteroperabilityIfd"
      MapData: TagNumber= 0XA20E Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneXResolution"
      MapData: TagNumber= 0XA20F Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneYResolution"
      MapData: TagNumber= 0XA210 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FocalPlaneResolutionUnit"
      MapData: TagNumber= 0XA217 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sensing"
      MapData: TagNumber= 0XA300 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FileSource"
      MapData: TagNumber= 0XA301 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneType"
      MapData: TagNumber= 0XA401 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CustomRendered"
      MapData: TagNumber= 0XA402 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureMode"
      MapData: TagNumber= 0XA403 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
      MapData: TagNumber= 0XA404 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoomRatio"
      MapData: TagNumber= 0XA405 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "FocalLengthIn35mmFilm"
      MapData: TagNumber= 0XA406 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SceneCaptureType"
      MapData: TagNumber= 0XA407 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "GainControl"
      MapData: TagNumber= 0XA408 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
      MapData: TagNumber= 0XA409 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
      MapData: TagNumber= 0XA40A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
      MapData: TagNumber= 0XA40C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SubjectDistanceType"
    MapIfd: Caption= "MakerNote"
     MapSubIfds: Count= 0
     MapDatas:
      Group: "CanonCameraSettings" TagNumber= 0X0001
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DataLength"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "MacroMode"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Formula= "SelfTimer"           = "Value/10"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Quality"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FlashMode"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ContinuousDrive"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "FocusMode"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "RecordMode"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageSize"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "EasyMode"
       MapData: Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "DigitalZoom"
       MapData: Index=  13 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Contrast"
       MapData: Index=  14 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Saturation"
       MapData: Index=  15 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
       MapData: Index=  16 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ISOSpeed"
       MapData: Index=  17 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "MeteringMode"
       MapData: Index=  18 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocusRange"
       MapData: Index=  19 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AFPoint"
       MapData: Index=  20 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "ExposureProgram"
       MapData: Index=  22 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LensType"
       MapData: Index=  23 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "LongFocal"
       MapData: Index=  24 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "ShortFocal"
       MapData: Index=  25 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalUnits"
       MapData: Index=  26 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "MaxApertureApex"     = "(Value/64)^2"
       MapData: Index=  27 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "MinApertureApex"     = "(Value/64)^2"
       MapData: Index=  28 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FlashActivity"
       MapData: Index=  29 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "FlashBits"
       MapData: Index=  32 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ContinuousDrive"
       MapData: Index=  33 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AESetting"
       MapData: Index=  34 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageStabilization"
       MapData: Index=  35 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DisplayAperture"
       MapData: Index=  36 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ZoomSourceWidth"
       MapData: Index=  37 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ZoomTargetWidth"
       MapData: Index=  39 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SpotMeteringMode"
       MapData: Index=  40 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "PhotoEffect"
       MapData: Index=  41 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ManualFlashOutput"
       MapData: Index=  42 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ColorTone"
       MapData: Index=  46 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SRAWQuality"
      Group: "CanonFocalInfo" TagNumber= 0X0002
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalType"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 5 Caption= "FocalLength"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalPlaneXSize"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FocalPlaneYSize"
      Group: "CanonFlashInfo?" TagNumber= 0X0003
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashInfo1"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashInfo2"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashInfo3"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashInfo4"
      Group: "CanonShotInfo" TagNumber= 0X0004
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DataLength"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AutoISO"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Formula= "BaseISO"          = "50*(Value/32-4)^2"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Formula= "MesuredEV"        = "Value/20"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "ApertureApex"     = "(Value/64)^2"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 3 Formula= "ExposureTimeApex" = "(1/(Value/32)^2)"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureCompensation"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WhiteBalance"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SlowShutter"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SequenceNumber"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "OpticalZoomCode"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Formula= "CameraTemperature"     = "Value/10"
       MapData: Index=  13 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashGuideNumber"
       MapData: Index=  14 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AFPointsInFocus"
       MapData: Index=  15 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "FlashBias"
       MapData: Index=  16 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AutoExposureBracketing"
       MapData: Index=  17 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AEBBracketValue"
       MapData: Index=  18 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ControlMode"
       MapData: Index=  19 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Unused"
       MapData: Index=  20 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Unused"
       MapData: Index=  21 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 2 Formula= "Aperture"              = "(Value/64)^2"
       MapData: Index=  22 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 3 Formula= "ExposureTime"          = "(1/(Value/32)^2)"
       MapData: Index=  23 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 0 Format= 1 Formula= "MeasuredEV1"           = "(Value/8)-6"
       MapData: Index=  24 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "BulbDuration"
       MapData: Index=  25 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  26 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "CameraType"
       MapData: Index=  27 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AutoRotate"
       MapData: Index=  28 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "NDFilter"
       MapData: Index=  29 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SelfTimer2"
       MapData: Index=  30 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  31 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  32 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  33 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "FlashOutput"
      MapData: TagNumber= 0X0006 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Model"
      MapData: TagNumber= 0X0009 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "OwnerName"
      MapData: TagNumber= 0X000C Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SerialNumber"
      Group: "CanonCameraInfo_EOS_7D" TagNumber= 0X000D
       MapData: Index=   0 ForceType= 3 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CameraInfoCanon7D"
       MapData: Index=   1 ForceType= 1 SubOffest= 0X00000002 Used= 0 Dump= 1 Format= 3 Formula= "TargetExposureTimeApex" = "(1/(Value/32)^2)"
       MapData: Index=   2 ForceType= 1 SubOffest= 0X00000003 Used= 0 Dump= 1 Format= 2 Formula= "TargetApertureApex"     = "e^(((Value/10)*ln(2))/2)"
       MapData: Index=   3 ForceType= 1 SubOffest= 0X00000004 Used= 0 Dump= 1 Format= 3 Formula= "ExposureTime"           = "(1/(Value/32)^2)"
       MapData: Index=   4 ForceType= 1 SubOffest= 0X00000005 Used= 0 Dump= 1 Format= 2 Formula= "ApertureApexUnit"       = "e^(((Value/10)*ln(2))/2)"
       MapData: Index=   5 ForceType= 1 SubOffest= 0X00000006 Used= 0 Dump= 1 Format= 1 Formula= "ISOApexUnit"            = "50*((Value/32)-4)^2"
       MapData: Index=   6 ForceType= 1 SubOffest= 0X00000007 Used= 0 Dump= 1 Format= 1 Caption= "HighlightTonePriority"
       MapData: Index=   7 ForceType= 1 SubOffest= 0X00000008 Used= 1 Dump= 1 Format= 1 Formula= "MeasuredEV2"            = "(Value/10)-1.5"
       MapData: Index=   8 ForceType= 1 SubOffest= 0X00000009 Used= 1 Dump= 1 Format= 1 Formula= "MeasuredEV"             = "(Value/10)-1.5"
       MapData: Index=   9 ForceType= 1 SubOffest= 0X00000015 Used= 0 Dump= 1 Format= 1 Caption= "FlashMeteringMode"
       MapData: Index=  10 ForceType= 1 SubOffest= 0X00000019 Used= 0 Dump= 1 Format= 1 Formula= "CameraTemperature"      = "Value/10"
       MapData: Index=  11 ForceType= 1 SubOffest= 0X0000001F Used= 0 Dump= 1 Format= 1 Caption= "FocalLength"
      MapData: TagNumber= 0X0007 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Firmware"
      Group: "CustomFunctions_EOS_7D" TagNumber= 0X000F
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DataLength"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SetButtonCrossKeysFunc"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LongExposureNoiseReduction"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FlashSyncSpeedAv"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Shutter-AELock"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "AFAssistBeam"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ExposureLevelIncrements"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "MirrorLockup"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ETTLII"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ShutterCurtainSync"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "MagnifiedView"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "LCDDisplayAtPowerOn"
      MapData: TagNumber= 0X0010 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CanonModelId"
      MapData: TagNumber= 0X0013 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ThumbnailImageValidArea"
      MapData: TagNumber= 0X0015 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SerialNumberFormat"
      MapData: TagNumber= 0X0019 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
      Group: "CanonAFInfo2_EOS_7D" TagNumber= 0X0026
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DataLength"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "FocusAreaMode"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "NumAFPoints"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ValidAFPoints"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageWidth"  
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ImageHeight"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFImageWidth"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFImageHeight"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFAreaWidth"
       MapData: Index=  27 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFAreaHeight"
       MapData: Index=  46 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFAreaXPositions"
       MapData: Index=  65 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "AFAreaYPositions"
      MapData: TagNumber= 0X0083 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "OriginalDecisionDataOffset"
      Group: "CanonFileInfo_EOS_7D" TagNumber= 0X0093
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DataLength"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Unused"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Unused"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "BracketMode"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BracketValue"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BracketShotNumber"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "RawJpgQuality"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "RawJpgSize"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "LongExposureNoiseReduction2"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "WBBracketMode"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "WBBracketValueAB"
       MapData: Index=  13 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "WBBracketValueGM"
       MapData: Index=  14 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "FilterEffect"
       MapData: Index=  15 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ToningEffect"
       MapData: Index=  16 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MacroMagnification"
       MapData: Index=  17 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MacroMagnification"
       MapData: Index=  18 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MacroMagnification"
       MapData: Index=  19 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MacroMagnification"
       MapData: Index=  20 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Formula= "FocusDistanceUpper" = "Value/100"
       MapData: Index=  21 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Formula= "FocusDistanceLower" = "Value/100"
       MapData: Index=  22 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  23 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  24 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
       MapData: Index=  25 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
      MapData: TagNumber= 0X0095 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 1 Dump= 1 Format= 1 Caption= "Lens"
      MapData: TagNumber= 0X0096 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "InternalSerialNumber"
      MapData: TagNumber= 0X0097 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "DustRemovalData"
      MapData: TagNumber= 0X0098 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "CropInfo"
      MapData: TagNumber= 0X0099 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
      MapData: TagNumber= 0X009A Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "???"
      Group: "ProcessingInfo" TagNumber= 0X00A0
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Length"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ToneCurve"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "Sharpness"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "SharpnessFrequency"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorRedLevel"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorBlueLevel"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "WhiteBalanceRed"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "WhiteBalanceBlue"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "WhiteBalance"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "ColorTemperature"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 1 Caption= "PictureStyle"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "DigitalGain"
       MapData: Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "WBShiftAB"
       MapData: Index=  13 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "WBShiftGM"
      Group: "MeasuredColor" TagNumber= 0X00AA
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Length"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MeasuredColor.1"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MeasuredColor.2"
       MapData: Index=   3 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MeasuredColor.3"
       MapData: Index=   4 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "MeasuredColor.4"
      MapData: TagNumber= 0X00B4 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "ColorSpace"
      MapData: TagNumber= 0X00D0 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "VRDOffset"
      Group: "SensorInfo" TagNumber= 0X00E0
       MapData: Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "Length"
       MapData: Index=   1 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorWidth"
       MapData: Index=   2 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorHeight"
       MapData: Index=   5 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorLeftBorder"
       MapData: Index=   6 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorTopBorder"
       MapData: Index=   7 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorRightBorder"
       MapData: Index=   8 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorBottomBorder"
       MapData: Index=   9 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BlackMaskLeftBorder"
       MapData: Index=  10 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BlackMaskTopBorder"
       MapData: Index=  11 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BlackMaskRightBorder"
       MapData: Index=  12 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "BlackMaskBottomBorder"
       MapData: Index=  15 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfo???"
       MapData: Index=  16 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 1 Format= 0 Caption= "SensorInfo???"
      MapData: TagNumber= 0X4001 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "ColorData"
      MapData: TagNumber= 0X4002 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "CRWParam"
      MapData: TagNumber= 0X4005 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "ColorInfo"
      MapData: TagNumber= 0X4008 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "BlackLevel"
      MapData: TagNumber= 0X4009 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "???"
      MapData: TagNumber= 0X4010 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "CustomPictureStyleFileName"
      MapData: TagNumber= 0X4011 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "0x4011NoDump"
      MapData: TagNumber= 0X4012 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "???"
      MapData: TagNumber= 0X4013 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "AFMicroAdj"
      MapData: TagNumber= 0X4015 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "VignettingCorr"
      MapData: TagNumber= 0X4016 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "VignettingCorr2"
      MapData: TagNumber= 0X4017 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "???"
      MapData: TagNumber= 0X4018 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "LightingOpt"
      MapData: TagNumber= 0X4019 Index=   0 ForceType= 0 SubOffest= 0X00000000 Used= 0 Dump= 0 Format= 0 Caption= "LensInfo"
[Licence]
 Email: "bernard_tran@hotmail.com"
 MacAdress: 00 00 00 00 00 00 00 00
 CheckSum: 12554877452
 Version: "2012 01 19"
 OS: "Windows7x64"

