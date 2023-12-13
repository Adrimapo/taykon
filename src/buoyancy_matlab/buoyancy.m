% Constants
g = 9.81;              % Acceleration due to gravity (m/s²)
rho_water = 997;       % Density of water (kg/m³)

% Dimensions of the robot shell
length_box = 0.05;     % 5 cm 
width_box = 0.17;      % 17 cm 
height_box = 0.098;    % 9.8 cm 

% Calculate the volume of the shell
total_volume = length_box * width_box * height_box;

% Volume range for the shell (submerged volume between 0% and 50%)
volume_percentage_range = linspace(0, 1, 100);
volume_range = volume_percentage_range * total_volume;

% Buoyancy force calculation (Archimedes' Principle)
buoyancy_force = rho_water * g * volume_range;

% Error range for the submerged volume due to robot arms (+-5%)
error_percentage = 0.05;
error_volume = max(0, error_percentage * total_volume); % Ensure non-negative error

%% Plotting with error area
figure;
hold on;

% Plot buoyancy force
plot(volume_percentage_range * 100, buoyancy_force, 'LineWidth', 2);

% Plot error area
error_area_upper = buoyancy_force + rho_water * g * error_volume;
error_area_lower = buoyancy_force - rho_water * g * error_volume;

% Create a filled area between upper and lower error bounds
fill([volume_percentage_range*100, fliplr(volume_percentage_range*100)], [error_area_upper, fliplr(error_area_lower)], 'b', 'FaceAlpha', 0.3, 'EdgeColor', 'none', 'DisplayName', 'Error Range');

xlabel('Submerged Volume (%)');
ylabel('Buoyancy Force (N)');
title('Buoyancy Force vs Volume Submerged (Archimedes Principle)');
grid on;

ylim([0, max(buoyancy_force) + max(rho_water * g * error_volume)]);

legend('Buoyancy Force','Error Range');
hold off;
