"use strict";
(function () {
    const divBins = document.getElementById("bins");
    const BIN_SIZE = 15;

    const bins = [];
    const rectColors = ["#FF0000", "#00FF00", "#0000FF", "#FFFF00", "#00FFFF", "#FF00FF", "#000000"];

    const loadBins = function (size) {
        while (divBins.firstChild) {
            divBins.firstChild.remove()
        }
        bins.length = 0;

        for (let i = 0; i < size.length; i += 2) {
            const div = document.createElement("div");
            const canvas = document.createElement("canvas");
            canvas.width = size[i] * (BIN_SIZE + 1) + 1;
            canvas.height = size[i + 1] * (BIN_SIZE + 1) + 1;
            div.appendChild(canvas);
            const divText = document.createElement("div");
            divText.innerText = `${i / 2}: ${size[i]} x ${size[i + 1]}`;
            div.appendChild(divText);
            const customDivText = document.createElement("div");
            customDivText.innerText = ``;
            div.appendChild(customDivText);
            divBins.appendChild(div);
            const ctx = canvas.getContext("2d");

            const bin = {
                canvas: canvas,
                div: div,
                customDiv: customDivText,
                ctx: ctx,
                width: size[i],
                height: size[i + 1]
            };
            drawGrid(bin);
            bins.push(bin);
        }
    };

    const drawGrid = function (bin) {
        bin.ctx.fillStyle = "#C0C0C0";
        bin.ctx.fillRect(0, 0, bin.canvas.width, bin.canvas.height);
        bin.ctx.fillStyle = "white";
        for (let x = 0; x < bin.width; x++) {
            for (let y = 0; y < bin.height; y++) {
                bin.ctx.fillRect(x * (BIN_SIZE + 1) + 1, y * (BIN_SIZE + 1) + 1, BIN_SIZE, BIN_SIZE);
            }
        }
    };

    const invertHex = function (hex) {
        return (Number(`0x1${hex}`) ^ 0xFFFFFF).toString(16).substr(1).toUpperCase()
    };

    const drawRectangle = function (bin, x, y, w, h, color, index) {
        bin.ctx.fillStyle = color;
        bin.ctx.fillRect(x * (BIN_SIZE + 1) + 1, y * (BIN_SIZE + 1) + 1, w * BIN_SIZE + (w - 1), h * BIN_SIZE + (h - 1));
        bin.ctx.fillStyle = "#" + invertHex(color.substr(1));
        bin.ctx.textAlign = "center";
        bin.ctx.textBaseline = "middle";
        bin.ctx.font = Math.min(w * BIN_SIZE / 2, h * BIN_SIZE / 2) + "px sans-serif";
        bin.ctx.fillText(`${index}`,
            x * (BIN_SIZE + 1) + 1 + (w * BIN_SIZE + (w - 1)) / 2,
            y * (BIN_SIZE + 1) + 1 + (h * BIN_SIZE + (h - 1)) / 2);
    };

    const countRectangles = function (bin, rectangles) {
        let count = 0;
        for (let i = 0; i < rectangles.length; i++) {
            const rect = rectangles[i];
            if (rect.x < 0 || rect.y < 0 || rect.x + rect.w > bin.width || rect.y + rect.h > bin.height) {
                continue;
            }
            count++;
        }
        return count;
    };

    const drawRectangles = function (prefix, bin, rectangles) {
        let count = 0;
        let area = 0;
        for (let i = 0; i < rectangles.length; i++) {
            const rect = rectangles[i];
            if (rect.x < 0 || rect.y < 0 || rect.x + rect.w > bin.width || rect.y + rect.h > bin.height) {
                continue;
            }
            drawRectangle(bin, rect.x, rect.y, rect.w, rect.h, rectColors[rect.c], rect.index);
            count++;
            area += rect.w * rect.h;
        }
        bin.customDiv.innerText = `${prefix} Rectangles: ${count}, Area: ${area}`;
        return count;
    };


    const sliceDivide = function (rectangles, divPt, x1, y1, x2, y2, x3, y3, x4, y4, depth, base, horizontal) {
        const minDepth = 4;
        const maxDepth = 13;
        const divProb = 0.7;
        const splitUniformity = 0.15;
        const balance = 0.5;
        const towardsCenter = 0.0;

        const cornerDist = Math.sqrt(Math.pow(divPt[0], 2) + Math.pow(divPt[1], 2));
        const random = Math.random;
        const abs = Math.abs;
        const floor = Math.floor;
        const bools = [true, false];

        if (depth == base) {
            if (x3 - x1 !== 0 && y3 - y1 !== 0) {
                rectangles.push({
                    x: x1,
                    y: y1,
                    w: x3 - x1,
                    h: y3 - y1
                });
            }
        } else {
            let randValHor = Math.floor(y1 + (y2 - y1) * random() * (1 - splitUniformity) + (y2 - y1) / 2 * splitUniformity);
            let randValVer = Math.floor(x1 + (x4 - x1) * random() * (1 - splitUniformity) + (x4 - x1) / 2 * splitUniformity);
            
            // horizontal split points
            let nx12 = (x1 + x2) / 2;
            let ny12 = randValHor;
            let nx34 = (x3 + x4) / 2;
            let ny34 = randValHor;
            
            // vertical split points
            let nx14 = randValVer;
            let ny14 = (y1 + y4) / 2;
            let nx23 = randValVer;
            let ny23 = (y2 + y3) / 2;
            
            // ternary assignments
            let a1 = x1;
            let a2 = y1;
            let a3 = (horizontal ? nx12 : x2);
            let a4 = (horizontal ? ny12 : y2);
            let a5 = (horizontal ? nx34 : nx23);
            let a6 = (horizontal ? ny34 : ny23);
            let a7 = (horizontal ? x4 : nx14);
            let a8 = (horizontal ? y4 : ny14);

            let b1 = (horizontal ? x2 : nx14);
            let b2 = (horizontal ? y2 : ny14);
            let b3 = (horizontal ? nx12 : nx23);
            let b4 = (horizontal ? ny12 : ny23);
            let b5 = (horizontal ? nx34 : x3);
            let b6 = (horizontal ? ny34 : y3);
            let b7 = (horizontal ? x3 : x4);
            let b8 = (horizontal ? y3 : y4);

            // center pt
            let center_aX = (a1 + a3) / 2;
            let center_aY = (a2 + a4) / 2;
            let center_bX = (b1 + b3) / 2;
            let center_bY = (b2 + b4) / 2;
            let dist_a = Math.sqrt(Math.pow(center_aX - divPt[0], 2) + Math.pow(center_aY - divPt[1], 2));
            let dist_b = Math.sqrt(Math.pow(center_bX - divPt[0], 2) + Math.pow(center_bY - divPt[1], 2));

            // Determine which way to split
            let r1horwider = (abs(a5 - a1) > abs(a6 - a2) ? false : true); // boolean for "is wider horizontally"
            let r2horwider = (abs(b5 - b1) > abs(b6 - b2) ? false : true);
            let r1hor = (random() > 1 - balance ? r1horwider : bools[floor(random() * 2)]); // divide by wider or random
            let r2hor = (random() > 1 - balance ? r2horwider : bools[floor(random() * 2)]);

            // Recursive calls or make and display rectangles
            let prob_a = towardsCenter * dist_a / cornerDist + (1 - towardsCenter) * (1 - divProb);
            let prob_b = towardsCenter * dist_b / cornerDist + (1 - towardsCenter) * (1 - divProb);
            let toDivide1 = (depth < maxDepth - minDepth ? random(1.0) : 1.0); // 1 if less than min depth
            if (toDivide1 > prob_a) { // 0.2
                sliceDivide(rectangles, divPt, a1, a2, a3, a4, a5, a6, a7, a8, depth - 1, base, r1hor);
            } else if (a5 - a1 !== 0 && a6 - a2 !== 0) {
                rectangles.push({
                    x: a1,
                    y: a2,
                    w: a5 - a1,
                    h: a6 - a2
                });
            }

            let toDivide2 = (depth < maxDepth - minDepth ? random() : 1.0);
            if (toDivide2 > prob_b) {
                sliceDivide(rectangles, divPt, b1, b2, b3, b4, b5, b6, b7, b8, depth - 1, base, r2hor);
            } else if (b5 - b1 !== 0 && b6 - b2 !== 0) {
                rectangles.push({
                    x: b1,
                    y: b2,
                    w: b5 - b1,
                    h: b6 - b2
                });
            }
        }
    }

    const randomRectangles = function (bin) {
        const rectangles = [];
        const maxDepth = 13;
        sliceDivide(rectangles, [bin.width / 2, bin.height / 2], 0, 0, 0, bin.height, bin.width, bin.height, bin.width, 0, maxDepth, 1, true);
        for (let i = 0; i < rectangles.length; i++) {
            let rect = rectangles[i];
            if (rect.w < 0) {
                rect.x += rect.w;
                rect.w = -rect.w;
            }
            if (rect.h < 0) {
                rect.y += rect.h;
                rect.h = -rect.h;
            }
        }
        rectangles.sort((a, b) => {
            if (a.y !== b.y) {
                return a.y - b.y;
            }
            return a.x - b.x;
        });
        for (let i = 0; i < rectangles.length; i++) {
            let rect = rectangles[i];
            rect.index = i;
            rect.c = i % rectColors.length;
        }
        return rectangles;
    }

    const ffdh = function (bin, rectangles, twophase) {
        // First Fit Decreasing Height
        rectangles.sort((a, b) => {
            if (b.h === a.h) {
                return b.index - a.index;
            }
            return b.h - a.h;
        });
        // for (let i = 0; i < rectangles.length; i++) {
        //     const rect = rectangles[i];
        //     if (rect.w < rect.h) {
        //         [rect.w, rect.h] = [rect.h, rect.w];
        //     }
        // }
        const grid = [];
        for (let i = 0; i < bin.height; i++) {
            grid[i] = [];
            for (let j = 0; j < bin.width; j++) {
                grid[i][j] = 0;
            }
        }
        for (let i = 0; i < rectangles.length; i++) {
            let rect = rectangles[i];
            rect.x = -1;
            rect.y = -1;
        }
        let currY = 0;
        while (true) {
            let placedAll = true;
            let maxH = undefined;
            let currX = 0;
            for (let i = 0; i < rectangles.length; i++) {
                let rect = rectangles[i];
                if (rect.x !== -1) {
                    continue;
                }
                if (currY + rect.h > bin.height) {
                    continue;
                }
                if (maxH === undefined) {
                    maxH = rect.h;
                } else if (rect.h > maxH) {
                    continue;
                }
                if (currX + rect.w > bin.width) {
                    continue;
                }
                rect.x = currX;
                rect.y = currY;
                for (let j = 0; j < rect.h; j++) {
                    for (let k = 0; k < rect.w; k++) {
                        grid[currY + j][currX + k] = 1;
                    }
                }
                currX += rect.w;
                placedAll = false;
            }
            if (placedAll) {
                break;
            }
            currY += maxH;
            if (twophase) {
                // phase 2
                currX = bin.width;
                for (let i = 0; i < rectangles.length; i++) {
                    let rect = rectangles[i];
                    if (rect.x !== -1) {
                        continue;
                    }
                    if (currY - rect.h < 0) {
                        continue;
                    }
                    if (currX - rect.w < 0) {
                        continue;
                    }
                    let canPlace = true;
                    for (let k = 0; k < rect.h; k++) {
                        for (let l = 0; l < rect.w; l++) {
                            if (grid[currY - rect.h + k][currX - rect.w + l] !== 0) {
                                canPlace = false;
                                break;
                            }
                        }
                    }
                    if (canPlace) {
                        rect.x = currX - rect.w;
                        rect.y = currY - rect.h;
                        for (let k = 0; k < rect.h; k++) {
                            for (let l = 0; l < rect.w; l++) {
                                grid[currY - rect.h + k][currX - rect.w + l] = 1;
                            }
                        }
                        currX -= rect.w;
                    }
                }
            }
        }

    };

    {
        let numbers = [20, 20];
        // numbers.push(30);
        // for (let i = 0; i < 2; i++) {
            // numbers.push(30);
        // }
        numbers[2] = numbers[0];
        numbers[3] = numbers[1];// + 10;
        numbers[4] = numbers[0] + 1;
        numbers[5] = numbers[1];// + 10;

        numbers[6] = numbers[2];
        numbers[7] = numbers[3];
        numbers[8] = numbers[4];
        numbers[9] = numbers[5];
         
        loadBins(numbers);

        // let bestDiff = 0;
        // let bestRectangles = undefined;

        // for (let i = 0; i < 1000 || bestRectangles == null; i++) {
        //     const rectangles = randomRectangles(bins[0]);
        //     const clone = JSON.parse(JSON.stringify(rectangles));
        //     ffdh(bins[3], rectangles, true);
        //     let b = countRectangles(bins[3], rectangles);

        //     ffdh(bins[4], rectangles, true);
        //     let c = countRectangles(bins[4], rectangles);
        //     let diff = b - c;
        //     if (diff > bestDiff || bestRectangles == null) {
        //         console.log(b, ", ", c);
        //         bestDiff = diff;
        //         bestRectangles = clone;
        //     }
        // }
        {
            const rectangles = randomRectangles(bins[0]);
            drawRectangles("Random rectangles", bins[0], rectangles);
            ffdh(bins[1], rectangles, false);
            drawRectangles("FFDH", bins[1], rectangles);
            ffdh(bins[2], rectangles, false);
            drawRectangles("FFDH", bins[2], rectangles);
            ffdh(bins[3], rectangles, true);
            drawRectangles("FFDH+FC", bins[3], rectangles);
            ffdh(bins[4], rectangles, true);
            drawRectangles("FFDH+FC", bins[4], rectangles);
            
        }
    }
})();
