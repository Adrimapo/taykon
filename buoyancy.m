% Constants
g = 9.81;              % Acceleration due to gravity (m/s²)
rho_water = 997;       % Density of water (kg/m³)
mass_range = linspace(0.4, 0.5, 100); % Mass in kg range for the robot (400-500 grams)

% Buoyancy force calculation (Archimede's Principle)
buoyancy_force = rho_water * mass_range * g;

% Plotting
figure;
plot(mass_range, buoyancy_force, 'LineWidth', 2);
xlabel('Robot Mass (kg)');
ylabel('Buoyancy Force (N/m³)');
title('Buoyancy vs Robot Mass (Archimedes Principle)');
grid on;
