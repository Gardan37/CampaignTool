# -------------------------------------------------
# Project created by QtCreator 2010-08-17T20:37:03
# -------------------------------------------------
QT += sql widgets
TARGET = CampaignTool
TEMPLATE = app
SOURCES += main.cpp \
    campaigntool.cpp \
    store.cpp \
    mapstore.cpp \
    force.cpp \
    forcelance.cpp \
    forcecompany.cpp \
    forcebattalion.cpp \
    forceregiment.cpp \
    forcerct.cpp \
    mapnode.cpp \
    mapmodel.cpp \
    mw.cpp \
    mwattribute.cpp \
    mwskill.cpp \
    mwtrait.cpp \
    mech.cpp \
    mechlocation.cpp \
    vehicle.cpp \
    vehiclelocation.cpp \
    equipment.cpp \
    weapon.cpp \
    weaponammo.cpp \
    dice.cpp \
    ../CharacterGenerator/attributemodel.cpp

# sheetmech.cpp \
# sheetmechlance.cpp \
# sheetvehiclelance.cpp \
# sheetwarrior.cpp \
HEADERS += campaigntool.h \
    store.h \
    mapstore.h \
    force.h \
    forcelance.h \
    forcecompany.h \
    forcebattalion.h \
    forceregiment.h \
    forcerct.h \
    mapnode.h \
    mapmodel.h \
    mw.h \
    mwattribute.h \
    mwskill.h \
    mwtrait.h \
    mech.h \
    mechlocation.h \
    vehicle.h \
    vehiclelocation.h \
    equipment.h \
    weapon.h \
    weaponammo.h \
    dice.h \
    ../CharacterGenerator/attributemodel.h

# sheetmech.h \
# sheetmechlance.h \
# sheetvehiclelance.h \
# sheetwarrior.h \
FORMS += campaigntool.ui
OTHER_FILES += missiondata/finalwar/finalwar.txt \
    store/mapstore.txt \
    store/mapsrandomtable.txt \
    missiondata/finalwar/map.txt
