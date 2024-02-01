import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import core.*;
import core.exceptions.*;

public class Connector {

	public static void main(String[] args) throws HlaSaveInProgressException, HlaRestoreInProgressException, HlaRtiException, HlaInternalException, HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInTimeAdvancingStateException, HlaObjectInstanceIsRemovedException, HlaUpdaterReusedException, HlaAttributeNotOwnedException { 
		// TODO Auto-generated method stub
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
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String input = null;
		System.out.println("Press \"c\" to exit");
		while(input != "c") {
			HlaPayloadManager payloadManager = hlaWorld.getHlaPayloadManager();
			try {
				HlaPayload payload = payloadManager.createLocalHlaPayload(); 
				HlaPayloadUpdater updater = payload.getHlaPayloadUpdater();
				updater.setAcceleration(new double[] {100.0});
				updater.sendUpdate();
			} catch (HlaSaveInProgressException | HlaRestoreInProgressException | HlaNotConnectedException
					| HlaInternalException | HlaRtiException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			try {
				input = reader.readLine();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			hlaWorld.advanceToNextFrame();
			System.out.println(input);
		}
		// simulate...
		try {
			hlaWorld.disconnect();
		} catch (HlaFederateOwnsAttributeException | HlaRtiException | HlaInternalException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.print("DisConnected");
	}

}
