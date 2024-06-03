function generatetbl() {
    const row = parseInt(document.getElementById("total").value, 10);
    let table = '<table id="table"><tr><th>Value</th><th>Weight</th></tr>';

    for (let i = 0; i < row; i++) {
        table += `<tr><td><input type="number" id="value_${i}" step="1"></td>`;
        table += `<td><input type="number" id="weight_${i}" step="1"></td></tr>`;
    }
    table += '</table>';
    table += '<button type="button" onclick="knapsackcalc()">Solve</button>';

    document.getElementById("inputus").innerHTML = table;
}

function copy(val1,val2,iter){
    for(let i=0;i<iter;i++){
        val1[i] = val2[i];
    }
}

function maksimumsort(ind,weight,cost,n){
    for(let i = 1; i < n; ++i){
         let maxind = i;
        for(let j = i; j>0; j--){
            if(cost[j]/weight[i] > cost[maxind]/weight[maxind]){
                maxind = j;
            }
        }
        [ind[i], ind[maxind]] = [ind[maxind], ind[i]];
        
    }
}

function algknapsack(ind, sol, weight, capacity, iter) {
    const d = [];
    for(let i = 0; i < iter; i++){
        d.push(0);
    }
    for (let i = 0; i < iter; i++) {
        d[ind[i]] = Math.floor(capacity / weight[ind[i]]); // Menghitung jumlah maksimum item yang dapat dimasukkan
    }
    console.log(d);
    for (let i = 0; i < iter; i++) {
        sol[ind[i]] = Math.min(d[ind[i]], Math.floor(capacity / weight[ind[i]])); // Menyesuaikan dengan jumlah maksimum
        console.log(Math.floor(capacity/weight[ind[i]]));
        capacity -= sol[ind[i]] * weight[ind[i]]; // Mengurangi kapasitas berdasarkan berat item yang dimasukkan
        if (capacity == 0) {
            break;
        }
    }
}

function totval(sol,val){
    let total=0;
    for(let i=0;i<sol.length;i++){
        total+=sol[i]*val[i]
    }

return total;
}

function knapsackcalc() {
    const row = parseInt(document.getElementById("total").value, 10);
    const ind = [];
    const solution = [];
    const values = [];
    const weights = [];
    const table = document.getElementById("table");
    const cap = parseInt(document.getElementById("cap").value, 10);
    let result='';

    for (let i = 0; i < row; i++) {
        const value = parseFloat(table.rows[i + 1].cells[0].children[0].value);
        const weight = parseInt(table.rows[i + 1].cells[1].children[0].value, 10);
        values.push(value);
        weights.push(weight);
        solution.push(0);
        ind.push(i);
    }

    maksimumsort(ind, weights, values, row);
    algknapsack(ind, solution, weights, cap, row);
    let totvalue = totval(solution,values);

    for(let i=0;i<row;i++){
        result+= "barang " + (i+1) + " sebanyak : " + solution[i] + " unit";
        result+= '<br>';
    }
    result += "dengan nilai sebanyak : " + totvalue;

    document.getElementById('output').innerHTML = result;
}
