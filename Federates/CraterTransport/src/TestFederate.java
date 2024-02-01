import core.*;
import core.exceptions.*;

public class TestFederate {

	public static void main(String[] args) throws HlaSaveInProgressException, HlaRestoreInProgressException, HlaRtiException, HlaInternalException, HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInTimeAdvancingStateException, HlaObjectInstanceIsRemovedException, HlaUpdaterReusedException, HlaAttributeNotOwnedException, HlaIllegalInstanceNameException, HlaInstanceNameInUseException { 
		// TODO Auto-generated method stub
		
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
		HlaPayload payload = payloadManager.createLocalHlaPayload();
		
		// TODO: Find a stopping point for our federate
		while(true) {
			try {
				// Manages variable/state changes and communicates them to the federation.
				// New instance must be created on every loop.
				HlaPayloadUpdater updater = payload.getHlaPayloadUpdater();
				
				// Example of how to update a variable (in this case of a Payload instance)
				// Ideally we'll call something like Physics.calculateAcceleration() or an
				// equivalent function.
				updater.setAcceleration(new double[] {100.0});
				
				// Packages all state/variable changes and sends them out to the federation
				// where other federates can pull the new values in and use them as needed.
				updater.sendUpdate();
			} catch (HlaSaveInProgressException | HlaRestoreInProgressException | HlaNotConnectedException
					| HlaInternalException | HlaRtiException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
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
