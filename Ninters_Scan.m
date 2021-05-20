repertoire = './';
executable = 'main';
input = 'Configuration.in ';
nsimul = 15;
ninters = logspace(1,4,nsimul);
paramstr = 'ninters'
param = ninters;
output = cell(1,nsimul);
for i = 1:nsimul
    output{i} = [paramstr, '=', num2str(param(i)), '.out'];
    cmd = sprintf('%s%s %s %s=%.15g output_energy=%s', repertoire, executable, input, paramstr, param(i), output{i})
    disp(cmd)
    system(cmd);
end

error = zeros(1,nsimul);
for i = 1:nsimul
    data = load(output{i});
    error(i) = abs(data(1,1)-1/8*pi*pi);
end

p = polyfit(log(param), log(error), 1);
tau = p(1);
kappa = exp(p(2));
figure % plot
p=loglog(param,error,'+');
nice_plot(p);
hold on
loglog(param,kappa*param.^tau, 'k-','Linewidth',1.5)
legend('Data',sprintf('y = %.3f * x^{%.2f}', kappa, tau));
set(gca,'fontsize',fs)
set(gcf,'Color','w')
xlabel('Number of intervals')
ylabel('Error')
grid on