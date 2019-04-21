A school project - snake game for Windows written mostly in plain C using Visual Studio (yuck).









- Pre optimálne fungovanie hry je vhodné v konzoli nastaviť font s rovnakou šírkou a výškou znakov (napríklad Raster Fonts 8x8).
  Had sa potom bude pohybovať rovnakou rýchlosťou aj v horizontálnom, aj vo vertikálnom smere.
- 10 najlepších skóre sa zapíše do súboru highscores.txt. Ak súbor neexistuje, program ho sám vytvorí.
- Ak existuje súbor map.txt v správnom formáte, hra z neho načíta prekážky.
  Formát súboru je nasledovný:
  - Hracia plocha je ohraničená znakom '#'. Veľkosť hracej plochy možno meniť, ale nesmie byť menšia ako 20x20.
  - Prekážky sú vyznačené znakom 'X'.
  - Na konci súboru nie je znak nového riadku. Nikde inde nie sú žiadne ďalšie prebytočné znaky.
  Ak súbor neexistuje, spustí sa hra bez načítania prekážok, s východzími rozmermi plochy.

Príklad mapy:
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
