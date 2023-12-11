% Given parameters
Np = 4;                % Number of propellers
propeller_diameter = 0.09; % Diameter of the propellers in meters (9 cm converted to meters)
hp = 0.08;             % Height of the propeller in meters (8 cm converted to meters)
rho_air = 1.293;       % Air density in kg/m^3
rho_water = 997;       % Water density in kg/m^3
theta = deg2rad(6);    % Blade angle in radians (converted from 6 degrees)
rpm_range = linspace(0, 2000, 100);  % RPM range from 0 to 6000 RPM

% Compute disk area (A) from propeller diameter
A = (pi * (propeller_diameter / 2)^2);

% Additional parameters for the formula
k1 = Np * 3 * A * hp;
k2 = 6 * A * tan(theta);

% Calculate lift force based on the provided formula
liftForce = zeros(size(rpm_range));

for i = 1:length(rpm_range)
    alpha = k1 * (rpm_range(i) / 60)^2;
    h_alpha = (k1 * hp * alpha^2) / (3 * (alpha + 6 * A * tan(theta)) + k2 * alpha^2);
    liftForce(i) = Np * rho_water * 9.81 * A * h_alpha;
end

% Plotting
figure;
plot(rpm_range, liftForce, 'LineWidth', 2, 'Color', 'red');
xlabel('RPM (Rotations per Minute)');
ylabel('Lift Force (N)');
title('Lift Force vs RPM');
grid on;
