% Robot params
propeller_diameter = 0.09;  % Diámetro de las hélices en metros
rpm_range = linspace(0, 2000, 100);  % Rango de RPM

% Conversión de RPM a velocidad lineal
lineal_vel = (rpm_range * pi * propeller_diameter) / 60;

% Gráfica
figure;
plot(rpm_range, lineal_vel, 'LineWidth', 2, 'Color', 'blue');
xlabel('RPM');
ylabel('Velocity in m/s');
title('RPM vs Velocity in m/s');
grid on;
