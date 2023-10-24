import java.io.File;

import core.LunarRoverFederate;
import core.LunarRoverFederateAmbassador;
import skf.config.ConfigurationFactory;
import model.LunarRover;
import model.Position;


public class LunarRoverMain {
	
	private static final File conf = new File("config/conf.json");
	
	public static void main(String[] args) throws Exception {
		
		LunarRover lunarRover = new LunarRover("LunarRover", "MoonCentricFixed",
				new Position (100, 200, 300));
		
		LunarRoverFederateAmbassador ambassador = new LunarRoverFederateAmbassador();
		LunarRoverFederate federate = new LunarRoverFederate(ambassador, lunarRover);
		
		// start execution
		federate.configureAndStart(new ConfigurationFactory().importConfiguration(conf));
	}

}
