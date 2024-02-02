package src;

import java.util.List;
import java.util.Properties;

import core.*;
import core.exceptions.*;

public class TestFederate2 {

	public static void main(String[] args) throws HlaSaveInProgressException, HlaRestoreInProgressException, HlaRtiException, HlaInternalException, HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInTimeAdvancingStateException, HlaObjectInstanceIsRemovedException, HlaUpdaterReusedException, HlaAttributeNotOwnedException, HlaIllegalInstanceNameException, HlaInstanceNameInUseException { 
		//Set federate settings
        String configPath = System.getProperty("user.dir") + "\\FederateConfig.properties";
        Properties props = System.getProperties();
        props.setProperty("core.settings", configPath);
		
		// Creates federation if this is the first federate connected,
		// connects to existing federation otherwise
		HlaWorld hlaWorld = HlaWorld.Factory.create();
		try {
			hlaWorld.connect();
		} catch (HlaInvalidLicenseException | HlaSaveInProgressException | HlaRestoreInProgressException
				| HlaNormalizerException | HlaConnectException | HlaFomException | HlaRtiException
				| HlaInternalException | HlaNotConnectedException | HlaInvalidLogicalTimeException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("Connected");

		// Manages Payload instances, allows you to handle and find different instances
		HlaPayloadManager payloadManager = hlaWorld.getHlaPayloadManager();
		
		// Single Payload instance, extends Dynamical Entity and has a number
		// of functions to retrive its values such as acceleration and position
        List<HlaPayload> list = payloadManager.getAllHlaPayloads();
        System.out.println(list.size());
		
		// TODO: Find a stopping point for our federate
		while(true) {
			
			hlaWorld.advanceToNextFrame();
		}
		
		// simulate...
		// Here we will do all of the federate cleanup necessary after it has finished running.
		// Unfortunately we can't run this code right now because we don't have a valid stopping
		// condition for our main loop.
		
		/*
		try {
			hlaWorld.disconnect();
		} catch (HlaFederateOwnsAttributeException | HlaRtiException | HlaInternalException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		*/
	}
}
