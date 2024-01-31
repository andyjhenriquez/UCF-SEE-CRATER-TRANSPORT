import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;

import core.*;
import core.exceptions.*;

public class TestFederate {

	public static void main(String[] args) throws HlaSaveInProgressException, HlaRestoreInProgressException, HlaRtiException, HlaInternalException, HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInTimeAdvancingStateException, HlaObjectInstanceIsRemovedException, HlaUpdaterReusedException, HlaAttributeNotOwnedException, HlaIllegalInstanceNameException, HlaInstanceNameInUseException { 
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
		// Connect federates
		System.out.println("Connected");
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String input = null;
		System.out.println("Press \"c\" to exit");
		HlaPayloadManager payloadManager = hlaWorld.getHlaPayloadManager();
		HlaPayload payload = payloadManager.getPayloadByHlaInstanceName("HLA.Payload1102");
		while(input != "c") {
			try {
				HlaPayloadUpdater updater = payload.getHlaPayloadUpdater();
				// Physics.calculate_acceleration(fdsf);
				updater.setAcceleration(new double[] {100.0});
				// Physics.calculate_position(hghyy)
				updater.sendUpdate();
				//System.out.println(payload.getAcceleration()[0]);
			} catch (HlaSaveInProgressException | HlaRestoreInProgressException | HlaNotConnectedException
					| HlaInternalException | HlaRtiException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
//			try {
//				input = reader.readLine();
//			} catch (IOException e) {
//				// TODO Auto-generated catch block
//				e.printStackTrace();
//			}
			hlaWorld.advanceToNextFrame();
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
