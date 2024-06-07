function generatetbl() {
    const row = parseInt(document.getElementById("total").value, 10);
    let table = `<table id="table" class="table table-bordered">
                    <thead class="thead-dark">
                        <tr>
                            <th>Item</th>
                            <th>Value</th>
                            <th>Weight</th>
                            <th>Available (IF M then -1)</th>
                        </tr>
                    </thead>
                    <tbody>`;

    for (let i = 0; i < row; i++) {
        table += `<tr>
                    <td>x` + (i+1) + `</td>
                    <td><input type="number" class="form-control" step="1"></td>
                    <td><input type="number" class="form-control" step="1"></td>
                    <td><input type="number" class="form-control" step="1"></td>
                </tr>`;
    }
    table += `</tbody>
            </table>`;
    table += '<button class="btn btn-success btn-block mt-2" onclick="knapsackcalc()">Solve</button>';

    document.getElementById("inputus").innerHTML = table;
}

function algknapsack(capacity, totvar, weight, value, available, selected) {
    // inisialisasi total nilai barang dengan 0
    let dp = Array.from({ length: totvar + 1 }, () => Array.from({ length: capacity + 1 }, () => 0));

    // menentukan total nilai barang agar maksimum
    for (let i = 1; i <= totvar; i++) {
        for (let j = capacity; j >= 0; j--) {
            for (let k = 0; k <= available[i-1] && k * weight[i-1] <= j; k++) {
                if (dp[i][j] < dp[i-1][j - k * weight[i-1]] + k * value[i-1]) {
                    dp[i][j] = dp[i-1][j - k * weight[i-1]] + k * value[i-1];
                }
            }
        }
    }

    // menentukan solusi
    let remainingCapacity = capacity;
    for (let i = totvar; i > 0; i--) {
        for (let k = 0; k <= available[i-1]; k++) {
            if (remainingCapacity >= k * weight[i-1] && dp[i][remainingCapacity] == dp[i-1][remainingCapacity - k * weight[i-1]] + k * value[i-1]) {
                selected[i-1] = k;
                remainingCapacity -= k * weight[i-1];
                break;
            }
        }
    }

    return dp[totvar][capacity];
}

function knapsackcalc() {
    const row = parseInt(document.getElementById("total").value, 10);
    const ind = [];
    const solution = [];
    const values = [];
    const weights = [];
    const avls = [];
    const table = document.getElementById("table");
    const cap = parseInt(document.getElementById("cap").value, 10);
    let result = '<h2>Result : </h2>';

    //mengambil nilai dari tabel sesuai variabel
    for (let i = 0; i < row; i++) {
        const value = parseFloat(table.rows[i + 1].cells[1].children[0].value);
        const weight = parseInt(table.rows[i + 1].cells[2].children[0].value, 10);
        const avl = parseInt(table.rows[i + 1].cells[3].children[0].value, 10);
        values.push(value);
        weights.push(weight);
        avls.push(avl);
        solution.push(0);
        ind.push(i);
    }

    //mendefinsikan variabel dengan batasan tidak terbatas
    for (let i = 0; i < row; i++) {
        if (avls[i] == -1) {
            avls[i] = Number.MAX_SAFE_INTEGER;
        }
    }

    const maxValue = algknapsack(cap, row, weights, values, avls, solution);

    for (let i = 0; i < row; i++) {
        result += "<hr>Item " + (i + 1) + " : " + solution[i] + " unit";
    }
    result += "<hr>With the total value is : " + maxValue;

    document.getElementById('output').innerHTML = result;
}
