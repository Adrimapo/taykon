% Given parameters
Nb = 4;                % N blades
propeller_diameter = 0.09; % Diameter of the propellers in m.
hp = 0.025;            % Height of the propeller in m.
h_blade = 0.008;       % Height of the blade in m.
rho_air = 1.293;       % Air density in kg/m³
rho_water = 997;       % Water density in kg/m³
theta = deg2rad(6);    % Approximated blade angle in rads
rpm_range = linspace(0, 2000, 100);  % RPM range from 0 to 6000 RPM
Cl = hp/h_blade; % Experimental value for lift coefficient,
                 % typically proportional to hp / h_blade.

% Convert RPM to airspeed
airspeed_range = (rpm_range * pi * propeller_diameter) / 60;

% Compute disk area (A) from propeller diameter
A = (pi * (propeller_diameter / 2)^2);

% Additional parameters for the formula
k1 = Nb * (propeller_diameter / 2)^3 * Cl;
k2 = 6 * A * tan(theta);

% Calculate lift force based on the provided formula
liftForce = zeros(size(rpm_range));

for i = 1:length(rpm_range)
    alpha = k1 * (rpm_range(i) / 60)^2; % rotational speed
    h_alpha = (k1 * hp * alpha^2) / (k1 * alpha^2 + k2);
    liftForce(i) = Nb * rho_water * 9.81 * A * h_alpha;
end

% Plotting
figure;
plot(airspeed_range, liftForce, 'LineWidth', 2, 'Color', 'red');
xlabel('Robot velocity (m/s)');
ylabel('Lift Force (N)');
title('Lift Force vs Robot velocity');
grid on;
