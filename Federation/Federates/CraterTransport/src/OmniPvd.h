#pragma once

#ifndef OMNIPVD_H
#define OMNIPVD_H

#include <PhysX/omnipvd/PxOmniPvd.h>
#include <PhysX/pvdruntime/OmniPvdWriter.h>
#include <PhysX/pvdruntime/OmniPvdFileWriteStream.h>

using namespace physx;

// Used for debug visualization in NVIDIA Omniverse
// using the PVD runtime extension
// Writes to a .ovd file which can be loaded in Omniverse
class OmniPvd {
public:
    static PxOmniPvd* initOmniPvd(PxFoundation& foundation) {
        PxOmniPvd* omniPvd = PxCreateOmniPvd(foundation);

        if (!omniPvd) {
            printf("Error: could not create PxOmniPvd!\n");
            return nullptr;
        }

        OmniPvdWriter* omniWriter = omniPvd->getWriter();
        
        if (!omniWriter) {
            printf("Error: could not create OmniPvdWriter\n");
            return nullptr;
        }

        OmniPvdFileWriteStream* fStream = omniPvd->getFileWriteStream();

        if (!fStream) {
            printf("Error: could not create OmniPvdFileWriteStream\n");
            return nullptr;
        }

        fStream->setFileName("OmniPvd_Output/visual_debugging.ovd");
        omniWriter->setWriteStream(static_cast<OmniPvdWriteStream&>(*fStream));

        return omniPvd;
    }
};
#endif