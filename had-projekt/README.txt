- Pre optimálne fungovanie hry je vhodné v konzoli nastavi font s rovnakou šírkou a vıškou znakov (napríklad Raster Fonts 8x8).
  Had sa potom bude pohybova rovnakou rıchlosou aj v horizontálnom, aj vo vertikálnom smere.
- 10 najlepších skóre sa zapíše do súboru highscores.txt. Ak súbor neexistuje, program ho sám vytvorí.
- Ak existuje súbor map.txt v správnom formáte, hra z neho naèíta prekáky.
  Formát súboru je nasledovnı:
  - Hracia plocha je ohranièená znakom '#'. Ve¾kos hracej plochy mono meni, ale nesmie by menšia ako 20x20.
  - Prekáky sú vyznaèené znakom 'X'.
  - Na konci súboru nie je znak nového riadku. Nikde inde nie sú iadne ïalšie prebytoèné znaky.
  Ak súbor neexistuje, spustí sa hra bez naèítania prekáok, s vıchodzími rozmermi plochy.

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