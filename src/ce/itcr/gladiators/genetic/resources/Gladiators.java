package ce.itcr.gladiators.genetic.resources;
import java.util.Random;

import ce.itcr.gladiators.genetic.QuickSort;

public class Gladiators {
	
	public Gladiator [] population = new Gladiator [100];
	Random random = new Random();
	
	public int getPopulationSize() {
		return population.length;
	}
	
	public void generateRandomPopulation() {
		for (int i = 0; i < population.length; i++) 
			population[i] = new Gladiator(new Chromosome(random.nextInt(10)));
	}
	
	public void sortGladiatorPopulation() {
		QuickSort quickSort = new QuickSort();
		quickSort.quickSort(population, 0, population.length-1);
	}
	
	public void printGladiatorPopulation() {
		int count = 0;
		for (Gladiator g : population) {
			System.out.println("-----------------------------");
			System.out.println("Gladiator: " + count);
			System.out.println("Fitness: " + g.getFitness());
			System.out.println();
			count++;
		}
	}
	
	public Gladiator getFittestGladiator() {
		Gladiator gladiator = population[population.length - 1];
		return gladiator;
	}
	
	public void replaceGladiator(Gladiator newGladiator) {
		sortGladiatorPopulation();
		population[0] = newGladiator;
		sortGladiatorPopulation();
	}

}
