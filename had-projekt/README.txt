- Pre optim�lne fungovanie hry je vhodn� v konzoli nastavi� font s rovnakou ��rkou a v��kou znakov (napr�klad Raster Fonts 8x8).
  Had sa potom bude pohybova� rovnakou r�chlos�ou aj v horizont�lnom, aj vo vertik�lnom smere.
- 10 najlep��ch sk�re sa zap�e do s�boru highscores.txt. Ak s�bor neexistuje, program ho s�m vytvor�.
- Ak existuje s�bor map.txt v spr�vnom form�te, hra z neho na��ta prek�ky.
  Form�t s�boru je nasledovn�:
  - Hracia plocha je ohrani�en� znakom '#'. Ve�kos� hracej plochy mo�no meni�, ale nesmie by� men�ia ako 20x20.
  - Prek�ky s� vyzna�en� znakom 'X'.
  - Na konci s�boru nie je znak nov�ho riadku. Nikde inde nie s� �iadne �al�ie prebyto�n� znaky.
  Ak s�bor neexistuje, spust� sa hra bez na��tania prek�ok, s v�chodz�mi rozmermi plochy.

Pr�klad mapy:
##############################################
#                                            #
#       X                                    #
#       X                                    #
#        X                                   #
#      XXXXX                                 #
#          X                                 #
#          X                                 #
#          X                                 #
#           X                                #
#            X                               #
#             X                              #
#              XXXXXXXXX                     #
#                                            #
#                                            #
#                                            #
#                                            #
#                                            #
#                       XXXXX                #
#                           X                #
#                           X                #
#                           X                #
#                           X                #
#                           X                #
##############################################