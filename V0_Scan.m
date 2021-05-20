repertoire = './';
executable = 'main';
input = 'Configuration.in ';
nsimul = 4;
V0 = logspace(1.5,3,nsimul)
paramstr = 'V0'
param = V0;
output = cell(1,nsimul);
for i = 1:nsimul
    output{i} = [paramstr, '=', num2str(param(i)), '.out'];
    cmd = sprintf('%s%s %s %s=%.15g output=%s', repertoire, executable, input, paramstr, param(i), output{i})
    disp(cmd)
    system(cmd);
end

figure
for i = 1:nsimul
    data = load(output{i});
    x = data(:,1);
    psi = data(:,2);
    p=plot(x,psi);
    nice_plot(p);
    hold on
end
xlabel('x')
ylabel('\psi')
legend('V_0=31','V_0=100','V_0=316','V_0=1000')
hold off

