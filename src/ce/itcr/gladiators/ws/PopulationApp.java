package ce.itcr.gladiators.ws;

import ce.itcr.gladiators.ws.res.PopulationsResource;
import ce.itcr.gladiators.ws.res.gladiators.GladiatorsResource;
import ce.itcr.gladiators.ws.res.towers.TowersResources;

import javax.ws.rs.ApplicationPath;
import javax.ws.rs.core.Application;
import java.util.HashSet;
import java.util.Set;

@ApplicationPath("/")
public class PopulationApp extends Application {

    public Set<Class<?>> getClasses() {
        Set<Class<?>> classes = new HashSet<>();
        classes.add(PopulationsResource.class);
        classes.add(GladiatorsResource.class);
        classes.add(TowersResources.class);
        return classes;
    }
}