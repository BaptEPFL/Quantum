Run_Load

%{
%% First Wave Functions for the Square Well
kpos = pi/2*[1 3 5];
kneg = pi*[1 2 3];
psi1 = @(x) cos(kpos(1).*x);
psi2 = @(x) cos(kpos(2).*x);
psi3 = @(x) cos(kpos(3).*x);
psi4 = @(x) sin(kneg(1).*x);
psi5 = @(x) sin(kneg(2).*x);
psi6 = @(x) sin(kneg(3).*x);
%}

%% First wave functions for the harmonic oscillator

%points = linspace(-1,1,1000);
points = x;
%potential = 4*points.*points-1.5;
initialise_eigen_modes

%% Compare numerical and analytical solutions for the harmonic oscillator
%{
figure
p=plot(x1,psi1,x2,psi2,x3,psi3);
nice_plot(p)
hold on
p=plot(points,potential)
nice_plot(p)
hold on
p=plot(points,phivalues1)
nice_plot(p)
hold on
p=plot(points,phivalues2)
nice_plot(p)
hold on
p=plot(points,phivalues3)
nice_plot(p)
legend('E_0=5.00153','E_1=15.0268','E_2=25.2065','\phi_0','\phi_1','\phi_2','NumColumns',2)
xlabel('x')
ylabel('Wave functions, Rescaled potential')

legend(num2str(E))
figure
p=plot(x,psi.*psi);
nice_plot(p)

hold on
p=plot(x,psi1(x),'--','Linewidth',1.5);
nice_plot(p)
hold on
p=plot(xbis,psibis);
nice_plot(p)
hold on
p=plot(x,psi4(x),'--','Linewidth',1.5);
nice_plot(p)
legend('Analytic First mode','Numerical First mode','Analytic Second mode','Numerical Second mode','Location','Southwest')
xlabel('x')
ylabel('\psi')

%% Compare x^n potentials
figure
p=plot(x1,psi1);
nice_plot(p)
hold on
p=plot(x3,psi3)
nice_plot(p)
hold on
p=plot(x2,psi2)
nice_plot(p)
xlabel('x')
ylabel('\psi')
legend('n=1','n=2','n=5')
%}

%% Lenhard-Jones problem

figure
pl = plot(x,psi,'+')
nice_plot(pl)
hold on
pl = plot(x,phivalues1,'-')
nice_plot(pl)
hold off
drawnow
