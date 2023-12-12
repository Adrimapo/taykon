% Constants
g = 9.81;              % Acceleration due to gravity (m/s²)
mass = 0.5;            % Assume a constant mass for the robot (kg)

% Density range for fresh water at different temperatures
temperature_range = 0:5:30; % Temperature in degrees Celsius
rho_freshwater = 997 * (1 - 0.00021 * (temperature_range - 20)); % Density of fresh water (kg/m³)

% Density range for saltwater at different temperatures
rho_saltwater = 1025 * (1 - 0.00023 * (temperature_range - 20)); % Density of saltwater (kg/m³)

% Buoyancy force calculation for fresh water and saltwater at different temperatures
buoyancy_freshwater = rho_freshwater * mass * g;
buoyancy_saltwater = rho_saltwater * mass * g;

% Plotting
figure;

% Plot for fresh water
subplot(2,1,1);
plot(temperature_range, buoyancy_freshwater, 'LineWidth', 2);
xlabel('Water Temperature (\circC)');
ylabel('Buoyancy Force (N)');
title('Equilibrium Point Buoyancy Force in Fresh Water (Sea level)');
grid on;

% Plot for saltwater
subplot(2,1,2);
plot(temperature_range, buoyancy_saltwater, 'LineWidth', 2);
xlabel('Water Temperature (\circC)');
ylabel('Buoyancy Force (N)');
title('Equilibrium Point Buoyancy Force in Saltwater (Sea level)');
grid on;
