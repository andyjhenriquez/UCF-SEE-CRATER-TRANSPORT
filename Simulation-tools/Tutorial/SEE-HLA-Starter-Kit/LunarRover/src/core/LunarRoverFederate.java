package core;

import hla.rti1516e.exceptions.AttributeNotDefined;
import hla.rti1516e.exceptions.AttributeNotOwned;
import hla.rti1516e.exceptions.CallNotAllowedFromWithinCallback;
import hla.rti1516e.exceptions.ConnectionFailed;
import hla.rti1516e.exceptions.CouldNotCreateLogicalTimeFactory;
import hla.rti1516e.exceptions.CouldNotOpenFDD;
import hla.rti1516e.exceptions.ErrorReadingFDD;
import hla.rti1516e.exceptions.FederateNotExecutionMember;
import hla.rti1516e.exceptions.FederationExecutionDoesNotExist;
import hla.rti1516e.exceptions.IllegalName;
import hla.rti1516e.exceptions.InconsistentFDD;
import hla.rti1516e.exceptions.InteractionClassNotDefined;
import hla.rti1516e.exceptions.InteractionClassNotPublished;
import hla.rti1516e.exceptions.InteractionParameterNotDefined;
import hla.rti1516e.exceptions.InvalidInteractionClassHandle;
import hla.rti1516e.exceptions.InvalidLocalSettingsDesignator;
import hla.rti1516e.exceptions.InvalidObjectClassHandle;
import hla.rti1516e.exceptions.NameNotFound;
import hla.rti1516e.exceptions.NotConnected;
import hla.rti1516e.exceptions.ObjectClassNotDefined;
import hla.rti1516e.exceptions.ObjectClassNotPublished;
import hla.rti1516e.exceptions.ObjectInstanceNameInUse;
import hla.rti1516e.exceptions.ObjectInstanceNameNotReserved;
import hla.rti1516e.exceptions.ObjectInstanceNotKnown;
import hla.rti1516e.exceptions.RTIinternalError;
import hla.rti1516e.exceptions.RestoreInProgress;
import hla.rti1516e.exceptions.SaveInProgress;
import hla.rti1516e.exceptions.SynchronizationPointLabelNotAnnounced;
import hla.rti1516e.exceptions.UnsupportedCallbackModel;

import java.net.MalformedURLException;
import java.text.SimpleDateFormat;
import java.util.Observable;
import java.util.Observer;
import java.util.TimeZone;

import model.LunarRover;
import model.Position;
import siso.smackdown.frame.FrameType;
import skf.config.Configuration;
import skf.core.SEEAbstractFederate;
import skf.core.SEEAbstractFederateAmbassador;
import skf.exception.PublishException;
import skf.exception.SubscribeException;
import skf.exception.UnsubscribeException;
import skf.exception.UpdateException;
import skf.model.interaction.modeTransitionRequest.ModeTransitionRequest;
import skf.model.object.annotations.ObjectClass;
import skf.model.object.executionConfiguration.ExecutionConfiguration;
import skf.model.object.executionConfiguration.ExecutionMode;
import skf.synchronizationPoint.SynchronizationPoint;
import skf.utility.JulianDateType;

public class LunarRoverFederate extends SEEAbstractFederate implements Observer {

	private static final int MAX_WAIT_TIME = 10000;
	
	
	private LunarRover lunarRover = null;
	private String local_settings_designator = null;
	
	private ModeTransitionRequest mtr = null;
	
	private SimpleDateFormat format = null;

	
	public LunarRoverFederate(SEEAbstractFederateAmbassador seefedamb, LunarRover lunarRover) {
		super(seefedamb);
		this.lunarRover  = lunarRover;
		this.mtr = new ModeTransitionRequest();
		
		this.format =  new SimpleDateFormat("yyyy-MM-dd HH:mm:ss z");
		format.setTimeZone(TimeZone.getTimeZone("UTC"));
	}

	@SuppressWarnings("unchecked")
	public void configureAndStart(Configuration config) throws ConnectionFailed, InvalidLocalSettingsDesignator, UnsupportedCallbackModel, 
														CallNotAllowedFromWithinCallback, RTIinternalError, CouldNotCreateLogicalTimeFactory, 
														FederationExecutionDoesNotExist, InconsistentFDD, ErrorReadingFDD, CouldNotOpenFDD, 
														SaveInProgress, RestoreInProgress, NotConnected, MalformedURLException, 
														FederateNotExecutionMember, NameNotFound, InvalidObjectClassHandle, AttributeNotDefined, 
														ObjectClassNotDefined, InstantiationException, IllegalAccessException, IllegalName, 
														ObjectInstanceNameInUse, ObjectInstanceNameNotReserved, ObjectClassNotPublished, 
														AttributeNotOwned, ObjectInstanceNotKnown, PublishException, UpdateException, 
														SubscribeException, InvalidInteractionClassHandle, InteractionClassNotDefined, 
														InteractionClassNotPublished, InteractionParameterNotDefined, UnsubscribeException, 
														InterruptedException, SynchronizationPointLabelNotAnnounced {
		// 1. configure the SKF framework
		super.configure(config);

		// 2. Connect on RTI
		/*
		 *For MAK local_settings_designator = "";
		 *For PITCH local_settings_designator = "crcHost=" + <crc_host> + "\ncrcPort=" + <crc_port>;
		 */
		local_settings_designator = "crcHost="+config.getCrcHost()+"\ncrcPort="+config.getCrcPort();
		super.connectToRTI(local_settings_designator);

		// 3. join the SEE Federation execution
		super.joinFederationExecution();
		
		// 4. Subscribe the Subject
		super.subscribeSubject(this);
		
		/*
		 * 5. Check if the federate is a Late Joiner Federate. 
		 * All the Federates of the SEE Teams must be Late Joiner.
		 */
		if(!SynchronizationPoint.INITIALIZATION_STARTED.isAnnounced()){
			
			// 6. Wait for the announcement of the Synch-Point "initialization_completed"
			super.waitingForAnnouncement(SynchronizationPoint.INITIALIZATION_COMPLETED, MAX_WAIT_TIME);

			/* 7. Wait for announcement of "objects_discovered", and Federation
			 * Specific Mutiphase Initialization Synch-Points
			 */
			// -> skipped
			
			/* 8. Subscribe Execution Control Object Class Attributes
			 * and wait for ExCO Discovery
			 */
			super.subscribeElement((Class<? extends ObjectClass>) ExecutionConfiguration.class);
			super.waitForElementDiscovery((Class<? extends ObjectClass>) ExecutionConfiguration.class, MAX_WAIT_TIME);
			
			// 9. Request ExCO update
			while(super.getExecutionConfiguration() == null){
				super.requestAttributeValueUpdate((Class<? extends ObjectClass>) ExecutionConfiguration.class);
				Thread.sleep(10);
			}
				
			// 10. Publish MTR Interaction
			super.publishInteraction(this.mtr);
			
			/* 11. Publish and Subscribe Object Class Attributes
			 * and Interaction Class Parameters
			 * 
			 * 12. Reserve All Federate Object Instance Names
			 * 
			 * 13. Wait for All Federate Object Instance Name Reservation
			 * Success/Failure Callbacks
			 * 
			 * 14. Register Federate Object Instances
			 */
			super.publishElement(lunarRover, "LunarRover");
			super.subscribeReferenceFrame(FrameType.AitkenBasinLocalFixed);
			
			// 15. Wait for All Required Objects to be Discovered
			// -> Skipped
			
			/* 16. Setup HLA Time Management and Query GALT, Compute HLTB and 
			 * Time Advance to HLTB
			 */
			super.setupHLATimeManagement();
			
			// 17. Achieve "objects_discovered" Sync-Point and wait for synchronization
			// -> Skipped
		}
		else
			throw new RuntimeException("The federate " + config.getFederateName() + "is not a Late Joiner Federate");
		
		//18. Start simulation execution
		super.startExecution();
		
	}

	@Override
	protected void doAction() {
		
		/* Time information related to the Federate */
		System.out.println("getFederateJoinHLALogicalTimeValue "+this.getTime().getFederateJoinHLALogicalTimeValue());
		System.out.println("getFederateJoinTimeAsJulianDate(JulianDateType.TRUNCATED) "+ this.getTime().getFederateJoinTimeAsJulianDate(JulianDateType.TRUNCATED));
		System.out.println(format.format(this.getTime().getFederateJoinTimeAsCalendar().getTime()));
		System.out.println(this.getTime().getFederateTimeCycle());
		
		/* Time information related to the Federation */
		System.out.println("getFederationTime "+ this.getTime().getFederationTimeCycle());
		System.out.println(format.format(this.getTime().getFederationTimeAsCalendar().getTime()));
		System.out.println("getFederationTimeAsJulianDate "+this.getTime().getFederationTimeAsJulianDate(JulianDateType.DATE));
		System.out.println("getFederationTimeAsJulianDate "+this.getTime().getFederationTimeAsJulianDate(JulianDateType.MODIFIED));
		System.out.println("getFederationTimeAsJulianDate "+this.getTime().getFederationTimeAsJulianDate(JulianDateType.REDUCED));
		System.out.println("getFederationTimeAsJulianDate "+this.getTime().getFederationTimeAsJulianDate(JulianDateType.TRUNCATED));

		Position curr_pos = this.lunarRover.getPosition();
		curr_pos.setX(curr_pos.getX()+10); // update the x coordinate

		try {

			super.updateElement(this.lunarRover);
			System.out.println(curr_pos);

		} catch (FederateNotExecutionMember | NotConnected | AttributeNotOwned
				| AttributeNotDefined | ObjectInstanceNotKnown | SaveInProgress
				| RestoreInProgress | RTIinternalError | IllegalName
				| ObjectInstanceNameInUse | ObjectInstanceNameNotReserved
				| ObjectClassNotPublished | ObjectClassNotDefined
				| UpdateException e) {
			e.printStackTrace();
		}

	}

	@Override
	public void update(Observable arg0, Object arg1) {

		System.out.println("The lunarRover has received an update");
		if(arg1 instanceof ExecutionConfiguration){
			super.setExecutionConfiguration((ExecutionConfiguration) arg1);
			
			/* Manage state transitions */
			if(super.getExecutionConfiguration().getCurrent_execution_mode() == ExecutionMode.EXEC_MODE_RUNNING &&
					super.getExecutionConfiguration().getNext_execution_mode() == ExecutionMode.EXEC_MODE_FREEZE){
				super.freezeExecution();
			}
			
			else if(super.getExecutionConfiguration().getCurrent_execution_mode() == ExecutionMode.EXEC_MODE_FREEZE &&
					super.getExecutionConfiguration().getNext_execution_mode() == ExecutionMode.EXEC_MODE_RUNNING){
				super.resumeExecution();
			}
			
			else if((super.getExecutionConfiguration().getCurrent_execution_mode() == ExecutionMode.EXEC_MODE_FREEZE || 
					super.getExecutionConfiguration().getCurrent_execution_mode() == ExecutionMode.EXEC_MODE_RUNNING ) &&
					super.getExecutionConfiguration().getNext_execution_mode() == ExecutionMode.EXEC_MODE_SHUTDOWN ){
				super.shudownExecution();
			}
			else
				System.out.println("ExecutionConfiguration status unknown");
			/* End Manage state transitions */
		}
		else
			System.out.println("unknown type");

	}

}
